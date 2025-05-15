#version 330 core

layout(location = 0) in vec3 l_pos;
layout(location = 1) in vec3 l_normal;

uniform mat4 u_modelView;
uniform mat4 u_projection;
uniform mat3 u_normal;

out vec3 o_Normal;
out vec3 o_Position;

void main() 
{
    o_Normal = normalize(u_normal * l_normal);
    o_Position = vec3(u_modelView * vec4(l_pos, 1.0));
    gl_Position = u_projection * u_modelView * vec4(l_pos, 1.0);
}