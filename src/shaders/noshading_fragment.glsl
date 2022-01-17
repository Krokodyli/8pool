#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform uint uObjectType;
uniform vec3 uColor;
uniform sampler2D uTexture;

void main()
{
  if((uObjectType % uint(2)) == uint(0)) {
    FragColor = vec4(uColor, 1.0f);
  } else {
    FragColor = texture(uTexture, texCoords); 
  }
}