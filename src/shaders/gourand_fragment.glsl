#version 330 core

in vec3 result;

out vec4 fragColor;

void main() {
  fragColor = vec4(result, 1.0f);
}