#version 460 core


layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_UV;
layout(location = 3) in vec3 a_Normal;


out      vec3 vs_viewDir;
out      vec3 vs_fragPos;
out      vec3 vs_position;
out      vec2 vs_UVcoord;

out      vec3 vs_color;
out flat vec3 vs_flatColor;

out      vec3 vs_normal;
out flat vec3 vs_flatNormal;


uniform mat4 u_projection;
uniform mat4 u_modelMatrix;
uniform mat3 u_normalMatrix;
uniform mat4 u_view;
uniform vec3 u_viewPos;



void main() {
    gl_Position = u_projection * u_view * u_modelMatrix * vec4(a_Position, 1.0);
    vs_color = a_Color;
    vs_flatColor = vs_color;
    vs_fragPos = vec3(u_modelMatrix * vec4(a_Position, 1.0));
    vs_normal = u_normalMatrix * a_Normal;
    vs_flatNormal = vs_normal;
    vs_UVcoord = a_UV;
    vs_position = a_Position;
    vs_viewDir = u_viewPos - vs_fragPos;
    float cameraDistance = length(vs_fragPos - u_viewPos);
}