#version 330 core

layout(location = 0) in vec3 l_pos;
layout(location = 1) in vec2 l_tex_coord;

out vec2 o_tex_coord;
out float o_distance;

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform vec3 u_camera_pos;

void main() 
{
    vec4 model_pos = u_model * vec4(l_pos, 1.0);
    gl_Position = u_projection * u_view * model_pos;

    o_tex_coord = l_tex_coord;
}