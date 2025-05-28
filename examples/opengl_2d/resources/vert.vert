#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 perspective;
uniform vec2 position;
uniform vec2 scale;

void main() {
    gl_Position = perspective * (vec4(aPos * vec3(scale, 1.0f) + vec3(position, 1.0), 1.0));
    // gl_Position = vec4(aPos, 1.0);
}
