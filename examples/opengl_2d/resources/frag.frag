#version 330 core

uniform vec3 color;
out vec4 FragColor;

void main()
{
    // FragColor = vec4(1.0, 0.5, 0.25, 1.0);
    FragColor = vec4(color, 1.0);
}