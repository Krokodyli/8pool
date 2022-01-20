#version 330 core

#define NR_LIGHTS 4

struct material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct light {
  uint type;

  vec3 position;
  vec3 direction;

  vec2 cut_off;
  vec3 attenuation;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

layout (location = 0) in vec3 p_pos;
layout (location = 1) in vec3 p_normal;
layout (location = 2) in vec2 p_tex_coords;

uniform mat4 u_model;
uniform mat3 u_normal_transform;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform uint u_object_type;
uniform vec3 u_color;
uniform sampler2D u_texture;
uniform material u_material;
uniform light u_lights[NR_LIGHTS];

uniform vec3 u_view_pos;

uniform float u_fog_factor;
uniform vec3 u_fog_color;

vec3 pos;
vec3 normal;
vec3 color;
vec3 view_dir;

vec3 calc_point_light(light light);
vec3 calc_spot_light(light light);
vec3 calc_object_color();
vec3 calc_fogged_color(vec3 color);

out vec3 v_color;

void main()
{
  vec4 global_pos = u_model * vec4(p_pos, 1.0f);
  pos = vec3(global_pos);
  color = calc_object_color();
  view_dir = normalize(u_view_pos - pos);
  normal = u_normal_transform * p_normal;

  vec3 result_color = vec3(0.0f);;
  if(u_object_type / uint(2) == uint(0)) {
    for(int i = 0; i < NR_LIGHTS; i++) {
      if(u_lights[i].type == uint(1))
        result_color += calc_point_light(u_lights[i]);
      else if(u_lights[i].type == uint(2))
        result_color += calc_spot_light(u_lights[i]);
    }
  }
  else {
    result_color = color;
  }

  v_color = calc_fogged_color(result_color);
  gl_Position = u_projection * u_view * global_pos;
}

vec3 calc_point_light(light light) {
  vec3 light_dir = normalize(light.position - pos);
  float diff = max(dot(normal, light_dir), 0.0);

  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_material.shininess);

  float distance = length(light.position - pos);
  float attenuation = 1.0 / (((distance * light.attenuation.z) 
                      + light.attenuation.y) * distance + light.attenuation.x);

  vec3 ambient = light.ambient * u_material.ambient * attenuation;
  vec3 diffuse = light.diffuse * diff * u_material.diffuse * attenuation;
  vec3 specular = light.specular * spec * u_material.specular * attenuation;

  return (ambient + diffuse) * color + specular;
}

vec3 calc_spot_light(light light) {
  vec3 light_dir = normalize(light.position - pos);
  float diff = max(dot(normal, light_dir), 0.0);

  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_material.shininess);

  float dist = length(light.position - pos);
  float attenuation = 1.0 / (((dist * light.attenuation.z) 
                      + light.attenuation.y) * dist + light.attenuation.x);

  float theta = dot(light_dir, normalize(-light.direction));
  float epsilon = light.cut_off.x - light.cut_off.y;
  float intensity = clamp((theta - light.cut_off.y) / epsilon, 0.0, 1.0);

  vec3 ambient = light.ambient * u_material.ambient * attenuation;
  vec3 diffuse = light.diffuse * diff * u_material.diffuse 
                 * attenuation * intensity;
  vec3 specular = light.specular * spec * u_material.specular 
                 * attenuation * intensity;

  return (ambient + diffuse) * color + specular;
}

vec3 calc_object_color() {
  if((u_object_type % (uint(2))) == uint(0))
    return u_color;
  else
    return vec3(texture(u_texture, p_tex_coords));
}

vec3 calc_fogged_color(vec3 color) {
  float dist = length(u_view_pos - pos);
  float fog_factor = -dist * u_fog_factor;
  fog_factor = clamp(exp(fog_factor), 0.0, 1.0);
  return mix(u_fog_color, color, fog_factor);
}