#version 330 core

flat in vec3 v_color;

out vec4 frag_color;

void main() {
  frag_color = vec4(v_color, 1.0f);
}