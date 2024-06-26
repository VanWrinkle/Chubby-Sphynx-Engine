#version 460 core
//vec3 pos, vec3 col, vec2 ST, vec3 normal

#define MAX_MODELS 32

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_UV;
layout(location = 3) in vec3 a_Normal;
layout(location = 4) in vec3 a_Tangent;
layout(location = 5) in vec3 a_Bitangent;
layout(location = 8) in float a_matID;

out      vec3 vs_viewDir;
out      vec3 vs_fragPos;
out      vec3 vs_position;
out      vec2 vs_UVcoord;
out      mat3 vs_TBN;

out    flat  int vs_matID;

out      vec3 vs_normal;
out flat vec3 vs_flatNormal;

out      vec3 vs_vertexColor;
out flat vec3 vs_flatVertexColor;

uniform mat4 u_projection;
uniform mat4 u_modelMatrix[MAX_MODELS];
uniform mat3 u_normalMatrix[MAX_MODELS];
uniform mat4 u_view;
uniform vec3 u_viewPos;


void main() {
    gl_Position = u_projection * u_view * u_modelMatrix[0] * vec4(a_Position, 1.0);
    vs_fragPos = vec3(u_modelMatrix[0] * vec4(a_Position, 1.0));
    vs_vertexColor = a_Color;
    vs_flatVertexColor = a_Color;
    vs_UVcoord = a_UV;
    vs_normal = u_normalMatrix[0] * a_Normal;
    vs_flatNormal = vs_normal;

    vec3 T = normalize(u_normalMatrix[0] * a_Tangent);
    vec3 B = normalize(u_normalMatrix[0] * a_Bitangent);
    vec3 N = vs_normal;
    vs_TBN = mat3(T, B, N);

    vs_position = a_Position;
    vs_viewDir = u_viewPos - vs_fragPos;
    vs_matID = max(min(int(a_matID), 2), 0);

    float cameraDistance = length(vs_fragPos - u_viewPos);
}