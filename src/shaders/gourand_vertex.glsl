#version 330 core
layout (location = 0) in vec3 lPos;
layout (location = 1) in vec3 lNormal;
layout (location = 2) in vec2 lTexCoords;

#define NR_LIGHTS 5

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  uint type;

  vec3 position;
  vec3 direction;

  vec2 cutOff;
  vec3 attenuation;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform uint uObjectType;
uniform vec3 uColor;
uniform sampler2D uTexture;
uniform Material uMaterial;
uniform Light uLights[NR_LIGHTS];

out vec3 result;

uniform mat4 uModel;
uniform mat3 uModelNormal;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 uViewPos;

vec3 norm;
vec3 pos;
vec3 viewDir;
vec3 color;

vec3 calculatePointLight(Light light);
vec3 calculateDirectionalLight(Light light);
vec3 calculateObjectColor();

void main() {
  gl_Position = uProjection * uView * uModel * vec4(lPos, 1.0f);

  norm = normalize(uModelNormal * lNormal);
  color = calculateObjectColor();
  pos = vec3(gl_Position);
  viewDir = normalize(uViewPos - pos);

  if(uObjectType / uint(2) == uint(0)) {
    result = vec3(0.0f, 0.0f, 0.0f);
    for(int i = 0; i < NR_LIGHTS; i++) {
      if(uLights[i].type == uint(1))
        result += calculatePointLight(uLights[i]);
      else if(uLights[i].type == uint(2))
        result += calculateDirectionalLight(uLights[i]);
    }
  }
  else {
    result = color;
  }
}

vec3 calculatePointLight(Light light) {
  vec3 lightDir = normalize(light.position - pos);
  float diff = max(dot(norm, lightDir), 0.0);

  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);

  float distance = length(light.position - pos);
  float attenuation = 1.0 / (((distance * light.attenuation.z) + light.attenuation.y) * distance + light.attenuation.x);

  vec3 ambient = light.ambient * uMaterial.ambient * attenuation;
  vec3 diffuse = light.diffuse * diff * uMaterial.diffuse * attenuation;
  vec3 specular = light.specular * spec * uMaterial.specular * attenuation;

  return (ambient + diffuse) * color + specular;
}

vec3 calculateDirectionalLight(Light light) {
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    
    vec3 ambient  = light.ambient  * uMaterial.ambient;
    vec3 diffuse  = light.diffuse  * diff * uMaterial.diffuse;
    vec3 specular = light.specular * spec * uMaterial.specular;

    return ambient + diffuse + specular;
}

vec3 calculateObjectColor() {
  if((uObjectType % uint(2)) == uint(0)) {
    return uColor;
  } else {
    return vec3(texture(uTexture, lTexCoords));
  }
}