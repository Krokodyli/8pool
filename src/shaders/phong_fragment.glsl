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

in vec3 v_pos;
in vec3 v_normal;
in vec2 v_tex_coords;

uniform vec3 u_view_pos;

uniform uint u_object_type;
uniform vec3 u_color;
uniform sampler2D u_texture;
uniform material u_material;
uniform light u_lights[NR_LIGHTS];

vec3 normal;
vec3 view_dir;
vec3 color;

vec3 calc_point_light(light light);
vec3 calc_spot_light(light light);
vec3 calc_object_color();
vec3 calc_fogged_color(vec3 color);

out vec4 frag_color;

void main() {
  normal = normalize(v_normal);
  color = calc_object_color();
  view_dir = normalize(u_view_pos - v_pos);

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

  frag_color = vec4(calc_fogged_color(result_color), 1.0f);
}

vec3 calc_point_light(light light) {
  vec3 light_dir = normalize(light.position - v_pos);
  float diff = max(dot(normal, light_dir), 0.0);

  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_material.shininess);

  float distance = length(light.position - v_pos);
  float attenuation = 1.0 / (((distance * light.attenuation.z) + light.attenuation.y) * distance + light.attenuation.x);

  vec3 ambient = light.ambient * u_material.ambient * attenuation;
  vec3 diffuse = light.diffuse * diff * u_material.diffuse * attenuation;
  vec3 specular = light.specular * spec * u_material.specular * attenuation;

  return (ambient + diffuse) * color + specular;
}

vec3 calc_spot_light(light light) {
  vec3 light_dir = normalize(light.position - v_pos);
  float diff = max(dot(normal, light_dir), 0.0);

  vec3 reflect_dir = reflect(-light_dir, normal);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_material.shininess);

  float distance = length(light.position - v_pos);
  float attenuation = 1.0 / (((distance * light.attenuation.z) + light.attenuation.y) * distance + light.attenuation.x);

  float theta = dot(light_dir, normalize(-light.direction));
  float epsilon = light.cut_off.x - light.cut_off.y;
  float intensity = clamp((theta - light.cut_off.y) / epsilon, 0.0, 1.0);

  vec3 ambient = light.ambient * u_material.ambient * attenuation;
  vec3 diffuse = light.diffuse * diff * u_material.diffuse * attenuation * intensity;
  vec3 specular = light.specular * spec * u_material.specular * attenuation * intensity;

  return (ambient + diffuse) * color + specular;
}

vec3 calc_object_color() {
  if((u_object_type % (uint(2))) == uint(0))
    return u_color;
  else
    return vec3(texture(u_texture, v_tex_coords));
}

vec3 calc_fogged_color(vec3 color) {
  return color;
}