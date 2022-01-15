#version 330 core
out vec4 FragColor;

in vec3 objectColor;
in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform sampler2D ourTexture;

void main()
{
    vec3 result;
    vec3 objectColor2 = vec3(texture(ourTexture, texCoords));
    if(lightPos.x != -1.0) {
      // constants
      vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

      // ambient
      float ambientStrength = 0.1;
      vec3 ambient = ambientStrength * lightColor;

      // diffuse
      vec3 norm = normalize(normal);
      vec3 lightDir = normalize(lightPos - fragPos);
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 diffuse = diff * lightColor;

      // specular
      float specularStrength = 0.5;
      vec3 viewDir = normalize(viewPos - fragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
      vec3 specular = specularStrength * spec * lightColor;

      // result
      result = (ambient + diffuse + specular) * objectColor2;
    }
    else {
         result = objectColor2;
    }
    FragColor = vec4(result, 1.0f);
} 