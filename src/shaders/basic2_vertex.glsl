#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 normal;
out vec3 objectColor;
out vec3 fragPos;
out vec2 texCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 color;

void main()
{
    vec4 modelPos = model * vec4(aPos, 1.0);
    fragPos = vec3(modelPos);
    gl_Position = projection * view * modelPos;
    objectColor = color;
    normal = mat3(transpose(inverse(model))) * aNormal;
    texCoords = aTexCoords;
}