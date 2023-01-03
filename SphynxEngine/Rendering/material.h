//
// Created by anmar on 12/16/2022.
//

#ifndef PROG2002_MATERIAL_H
#define PROG2002_MATERIAL_H

// external
#include <glm/glm.hpp>
// STD
#include <string>

/**
 * Struct for use with the Model class.
 */
struct Material {
    std::string diffuseTexture;
    glm::vec3   diffuseColor {1.0};
    std::string specularTexture;
    glm::vec3   specularColor {1.0};
    std::string normalTexture;
    float shininess {32};
    int normalTextureIndex {-1};
    int diffuseTextureIndex {-1};
    int specularTextureIndex {-1};
};

#endif //PROG2002_MATERIAL_H
