#version 330 core
layout (location = 0) in vec3 lPos;
layout (location = 1) in vec3 lNormal;
layout (location = 2) in vec2 lTexCoords;

out vec2 texCoords;
out vec3 color;

uniform uint uObjectType;
uniform vec3 uColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    color = uColor;
    texCoords = lTexCoords;
    gl_Position = uProjection * uView * uModel * vec4(lPos, 1.0f);
}