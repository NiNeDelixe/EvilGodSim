#version 330 core

in vec2 i_tex_coord;
out vec4 o_frag_color;

uniform sampler2D u_texture0;

void main() 
{
    vec4 texColor = texture(u_texture0, i_tex_coord);
    if(texColor.a < 0.1)
        discard;
    o_frag_color = texColor;
}