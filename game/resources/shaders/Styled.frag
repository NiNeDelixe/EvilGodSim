#version 330 core

precision highp float;

uniform vec3 u_lightDirection;
uniform vec3 u_baseColor;

in vec3 i_Normal;
in vec3 i_Position;

void main() 
{
    // base light
    float diffuse = max(0.0, dot(normalize(i_Normal), normalize(-u_lightDirection)));
    
    // Lighting quantization
    diffuse = floor(diffuse * 3.0) / 3.0; // 3 levels of light
    
    // base color with light
    vec3 color = u_baseColor * (0.7 + 0.3 * diffuse);
    
    // Contour lines
    float edge = 1.0 - max(0.0, dot(normalize(i_Normal), vec3(0.0, 0.0, 1.0)));
    if (edge > 0.95) 
    {
        color = vec3(0.0); // black texture
    }
    
    // Simple shadows
    if (i_Position.y < -0.5) 
    {
        color *= 0.8;
    }
    
    gl_FragColor = vec4(color, 1.0);
}