#version 460 core

out vec4 finalColor;

uniform vec3        u_borderColor;

void main() {
    finalColor = vec4(u_borderColor, 1.0);
}
