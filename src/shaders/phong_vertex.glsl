#version 330 core
layout (location = 0) in vec3 lPos;
layout (location = 1) in vec3 lNormal;
layout (location = 2) in vec2 lTexCoords;

out vec3 pos;
out vec3 normal;
out vec2 texCoords;

uniform uint uObjectType;
uniform vec3 uColor;

uniform mat4 uModel;
uniform mat3 uModelNormal;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
  pos = vec3(uModel * vec4(lPos, 1.0f));
  normal = uModelNormal * lNormal;
  texCoords = lTexCoords;
  gl_Position = uProjection * uView * vec4(pos, 1.0f);
}