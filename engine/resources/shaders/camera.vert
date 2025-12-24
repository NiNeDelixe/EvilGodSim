#version 330 core

layout (location = 0) in vec3 l_pos;

uniform mat4 u_model;
uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
    vec4 model_pos = u_model * vec4(l_pos, 1.0);
	gl_Position = u_projection * u_view * model_pos;
}