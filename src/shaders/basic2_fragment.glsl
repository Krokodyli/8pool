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
    vec3 objectColor2 = vec3(texture(ourTexture, texCoords));
    FragColor = vec4(objectColor2, 1.0f);
}