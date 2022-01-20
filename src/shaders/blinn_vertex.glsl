#version 330 core

layout (location = 0) in vec3 p_pos;
layout (location = 1) in vec3 p_normal;
layout (location = 2) in vec2 p_tex_coords;

uniform uint u_object_type;
uniform vec3 u_color;

uniform mat4 u_model;
uniform mat3 u_normal_transform;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 v_pos;
out vec3 v_normal;
out vec2 v_tex_coords;

void main()
{
  vec4 global_pos = u_model * vec4(p_pos, 1.0f);
  v_pos = vec3(global_pos);
  v_normal = u_normal_transform * p_normal;
  v_tex_coords = p_tex_coords;
  gl_Position = u_projection * u_view * global_pos;
}