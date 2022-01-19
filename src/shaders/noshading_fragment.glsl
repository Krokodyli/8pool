#version 330 core

in vec2 v_tex_coords;

uniform uint u_object_type;
uniform vec3 u_color;
uniform sampler2D u_texture;

out vec4 o_frag_color;

void main()
{
  if((u_object_type % uint(2)) == uint(0))
    o_frag_color = vec4(u_color, 1.0f);
  else
    o_frag_color = texture(u_texture, v_tex_coords);
}