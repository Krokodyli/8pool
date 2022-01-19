#version 330 core
layout (location = 0) in vec3 p_pos;
layout (location = 1) in vec3 p_normal;
layout (location = 2) in vec2 p_tex_coords;

uniform uint u_object_type;
uniform vec3 u_color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 v_tex_coords;

void main()
{
  v_tex_coords = p_tex_coords;
  gl_Position = u_projection * u_view * u_model * vec4(p_pos, 1.0f);
}