#version 460 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_projection;
uniform mat4 u_modelMatrix;
uniform mat4 u_view;

void main() {
    gl_Position = u_projection * u_view * u_modelMatrix * vec4(a_Position, 1.0);
}