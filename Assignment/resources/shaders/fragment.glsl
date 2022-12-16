#version 460 core

// 32 Slot version

#define MAX_LIGHTS 40
#define MAX_MAT_SLOTS 5
#define MAX_TEXTURES 32

in      vec3 vs_position;
in      vec3 vs_fragPos;
in      vec3 vs_vertexColor;
in flat vec3 vs_flatVertexColor;
in      vec2 vs_UVcoord;
in      vec3 vs_normal;
in flat vec3 vs_flatNormal;
in flat  int vs_matID;
in      vec3 vs_viewDir;
in      mat3 vs_TBN;

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
    int   diffuseTextureIndex;
    vec3  specularCol;
    int   specularTextureIndex;
    int   normalTextureIndex;
    float shininess;
};

uniform int         u_maxtextures;

uniform Material    u_materials[MAX_MAT_SLOTS];
uniform PointLight  u_lights[MAX_LIGHTS];
uniform int         u_totalLights = 0;
uniform bool        u_texturing = false;
uniform bool        u_lighting = false;
uniform float       u_opaqueness = 1.0;


uniform vec3        u_viewPos;
uniform vec3        u_ambientLighting;
uniform vec3        u_blockCol;
uniform bool        u_blending;

uniform sampler2D   u_textures[MAX_TEXTURES];





vec3 pointLighting( PointLight light, Material material, vec3 normal, vec3 viewDir, vec3 fragPos);


void main() {



    Material material;
    material = u_materials[vs_matID];
    vec3 viewDir = normalize(vs_viewDir);
    vec3 normal;
    normal = texture(u_textures[material.normalTextureIndex], vs_UVcoord).rgb;
    normal = normal*2.0 - 1.0;
    normal = normalize(vs_TBN*normal);



    if(u_texturing) {
        material.diffuseCol *= texture(u_textures[material.diffuseTextureIndex], vs_UVcoord).rgb;
        material.specularCol *= texture(u_textures[material.specularTextureIndex], vs_UVcoord).rgb;
    }

    vec3 ambient = material.diffuseCol * u_ambientLighting;

    vec3 lighting = { 0.0, 0.0, 0.0 };
    lighting += ambient;

    for(int i = 0; i < u_totalLights; i++) {
        lighting += pointLighting(u_lights[i], material, normal, viewDir, vs_fragPos);
    }

    if (u_lighting) {
        finalColor = vec4(lighting, u_opaqueness);
    } else {
        finalColor = vec4(material.diffuseCol, u_opaqueness);
    }
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

