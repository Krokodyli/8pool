#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal;
out vec3 objectColor;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 color;

void main()
{
    vec4 modelPos = model * vec4(aPos, 1.0);
    fragPos = vec3(modelPos);
    gl_Position = projection * view * modelPos;
    objectColor = vec3(1.0f, 0.0f, 0.0f);
    normal = mat3(transpose(inverse(model))) * aNormal;
}