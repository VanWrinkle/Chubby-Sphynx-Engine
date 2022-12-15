#version 460 core

#define MAX_LIGHTS 60
#define MAX_MAT_SLOTS 10

in      vec3 vs_position;
in      vec3 vs_color;
in flat vec3 vs_flatColor;
in flat vec3 vs_flatNormal;
in      vec2 vs_UVcoord;
in      vec3 vs_fragPos;
in      vec3 vs_viewDir;
in      vec3 vs_normal;

out vec4 finalColor;

struct PointLight{
    bool  isActive;
    vec3  position;
    vec3  ambient;
    vec3  diffuse;
    vec3  specular;

    float constant;
    float linear;
    float quadratic;
};


struct Material {
    vec3  diffuseCol;
    int   diffuseTexSlot;
    vec3  specularCol;
    int   specularTexSlot;
    float shininess;
};


uniform Material    u_materials[MAX_MAT_SLOTS];
uniform PointLight  u_lights[MAX_LIGHTS];
uniform int         u_materialSlot = 0;
uniform int         u_totalLights = 0;
uniform bool        u_cubeMode = false;
uniform samplerCube u_cubemap[16];
uniform sampler2D   u_2Dtexture[16];
uniform vec3        u_viewPos;
uniform vec3        u_ambientLighting;
uniform vec3        u_blockCol;
uniform bool        u_blending;


vec3 pointLighting( PointLight light, Material material, vec3 normal, vec3 viewDir, vec3 fragPos);


void main() {

    vec3 norm = (u_cubeMode)? vs_flatNormal : normalize(vs_normal);
    vec3 viewDir = normalize(vs_viewDir);
    Material material;
    material = u_materials[u_materialSlot];


    vec3 col;
    vec4 tex;
    if(u_cubeMode) {
        col = u_blockCol;
        tex = texture(u_cubemap[0], vs_position);
    } else {
        col = vs_flatColor;
        tex = texture(u_2Dtexture[0], vs_UVcoord);
    }

    float blendIntensity = (u_blending) ? 0.5 : 1.0;
    vec3 diffuseCol = mix(tex.rgb, col, blendIntensity);
    material.diffuseCol = diffuseCol;
    vec3 ambient = diffuseCol * u_ambientLighting;

    vec3 lighting = { 0.0, 0.0, 0.0 };
    lighting += ambient;

    for(int i = 0; i < u_totalLights; i++) {
        lighting += pointLighting(u_lights[i], material, norm, viewDir, vs_fragPos);
    }

    finalColor = vec4(lighting, 1.0);
}




/**
* Calculates and returns the lightcontribution to a fragment from a given PointLight
*/
vec3 pointLighting( PointLight light, Material material, vec3 normal, vec3 viewDir, vec3 fragPos) {
    vec3 lighting = {0.0, 0.0, 0.0};
    if(light.isActive) {
        float distance = length(fragPos - light.position);
        float attenuation = 1.0 / (  light.constant +
            distance * (light.linear + light.quadratic * distance)  );

        vec3 lightDir = (light.position - fragPos) / distance;
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow( max( dot(viewDir, reflectDir), 0.0 ), material.shininess);
        vec3 specular = material.specularCol * spec * light.specular;

        vec3 diffuse = max(dot(normal, lightDir), 0.0) * material.diffuseCol * light.diffuse;
        diffuse *= attenuation;
        specular *= attenuation;

        lighting += diffuse + specular + light.ambient;
    }
    return lighting;
}

