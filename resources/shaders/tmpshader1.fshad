#version 330 core
out vec4 FragColor;

in vec3 objectColor;
in vec3 normal;
in vec3 fragPos;

uniform vec3 viewPos;
uniform vec3 lightPos;

void main()
{
    vec3 result;
    if(lightPos.x != -1.0) {
      // constants
      vec3 lightColor = vec3(1.0f, 1.0f, 0.3f);

      // ambient
      float ambientStrength = 0.1;
      vec3 ambient = ambientStrength * lightColor;

      // diffuse
      vec3 norm = normalize(normal);
      vec3 lightDir = normalize(lightPos - fragPos);
      float diff = max(dot(norm, lightPos), 0.0);
      vec3 diffuse = diff * lightColor;

      // specular
      float specularStrength = 0.5;
      vec3 viewDir = normalize(viewPos - fragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
      vec3 specular = specularStrength * spec * lightColor;

      // result
      result = (ambient + diffuse + specular) * objectColor;
    }
    else {
         result = objectColor;
    }
    FragColor = vec4(result, 1.0f);
} 