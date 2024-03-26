//
// Created by andre on 16.11.22.
//

#ifndef PROG2002_LIGHTS_H
#define PROG2002_LIGHTS_H

#include "glm/glm.hpp"
#include <map>

std::vector<glm::vec3> distanceTable = {
        {0.0f, 1.0f, 3.0f},
        {7.0f, 0.7f, 1.8},
        {13.0f, 0.35f, 0.44f},
        {20.0f, 0.22f, 0.2f},
        {32.0f, 0.14f, 0.07f},
        {50.0f, 0.09f, 0.032f},
        {65.0f, 0.07f, 0.017f},
        {100.0f, 0.045f, 0.0075f},
        {160.0f, 0.027f, 0.0028f},
        {200.0f, 0.022f, 0.0019f},
        {325.0f, 0.014f, 0.0007},
        {600.0f, 0.007f, 0.0002f},
        {3250.0f, 0.014f, 0.000007f},
        { 10000.0f, 0.0f, 0.0f}
};

enum {
    POS = 1,
    AMB = 2,
    DIFF = 4,
    SPEC = 8,
    CONST = 16,
    LINEAR = 32,
    QUAD = 64
};

struct PointLight {
    bool isActive {true};
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 ambient {0.0f, 0.0f, 0.0f};
    glm::vec3 diffuse {1.0f, 1.0f, 1.0f};
    glm::vec3 specular{1.0f, 1.0f, 1.0f};
    float constant {1.0};
    float linear{0.09};
    float quadratic{0.032};

    /**
     * Interpolates between linear and quadratic factors for attenuation formula
     * based on distance. ~80% of light will have fallen off by the given distance.
     * @param distance
     */
    void setAttenuationByDistance(float distance) {
        distance *= 5.0f;
        constant = 1.0f;
        linear = 0.0f;
        quadratic = 0.0f;
        glm::vec3 previous(0.0f, 0.0f, 0.0f);
        for(const auto d : distanceTable) {
            if(previous.x < distance && distance < d.x ) {
                float t = (distance - previous.x) / (d.x - previous.x);
                linear = previous.y * (1 - t) + d.y * t;
                quadratic = previous.z * (1 - t) + d.z * t;
                break;
            } else {
                previous = d;
            }
        }
    }
};

/**
 * TODO: Not very user friendly due to high potential for mixup of uniforms by index
 */
class LightsManager {
private:
    int m_totalLights {};
    std::string m_uniformName;
    std::map<std::string, PointLight >m_lights;

public:


    explicit LightsManager(const std::string& uniformName) {
        m_uniformName = uniformName;
    }

    void addLight(const std::string &name, PointLight light) {
        m_totalLights++;
        m_lights.insert({ name, light});
    }

    /**
     * Uploads uniforms of all active light sources
     * @param shader - shader the uniforms will be uploaded to
     */
    void upload(Shader &shader) {
        shader.uploadUniformInt("u_totalLights", m_totalLights);
        int index = 0;
        for(const auto& light : m_lights) {
            std::string identifier(m_uniformName + "[" + std::to_string(index) + "].");
            shader.uploadUniformInt(identifier+ "isActive",light.second.isActive);
            if(light.second.isActive) {
                shader.uploadUniformVec3(identifier + "position", light.second.position);
                shader.uploadUniformVec3(identifier + "ambient",light.second.ambient);
                shader.uploadUniformVec3(identifier + "diffuse", light.second.diffuse);
                shader.uploadUniformVec3(identifier + "specular", light.second.specular);
                shader.uploadUniformFloat(identifier + "constant", light.second.constant);
                shader.uploadUniformFloat(identifier + "linear", light.second.linear);
                shader.uploadUniformFloat(identifier + "quadratic", light.second.quadratic);
            }
            index++;
        }
    }

    /**
     * Uploads the uniforms of -one- named light source
     * @param shader - shader the light is to be uploaded to
     * @param name - name of light source to have its uniforms uploaded
     * @param attributes - use bitwise | with PointLight class enums to enable light attribute upload
     */
    void upload(Shader &shader, const std::string &name, int attributes) {
        shader.uploadUniformInt("u_totalLights", m_totalLights);
        int index = 0;
        for(const auto& light : m_lights) {
            if(light.first == name) {
                std::string identifier(m_uniformName + "[" + std::to_string(index) + "].");
                shader.uploadUniformInt(identifier+ "isActive",light.second.isActive);
                if(light.second.isActive) {
                    if(attributes & POS) {
                        shader.uploadUniformVec3(identifier + "position", light.second.position);
                    }
                    if(attributes & AMB) {
                        shader.uploadUniformVec3(identifier + "ambient",light.second.ambient);
                    }
                    if(attributes & DIFF) {
                        shader.uploadUniformVec3(identifier + "diffuse", light.second.diffuse);
                    }
                    if(attributes & SPEC) {
                        shader.uploadUniformVec3(identifier + "specular", light.second.specular);
                    }
                    if(attributes & CONST) {
                        shader.uploadUniformFloat(identifier + "constant", light.second.constant);
                    }
                    if(attributes & LINEAR) {
                        shader.uploadUniformFloat(identifier + "linear", light.second.linear);
                    }
                    if(attributes & QUAD) {
                        shader.uploadUniformFloat(identifier + "quadratic", light.second.quadratic);
                    }
                }
            }
            index++;
        }
    }

    /**
     * Retrieves reference to a PointLight object by name
     * @param name - name of light source
     * @return reference to light source
     */
    PointLight& operator[] (const std::string &name) {
        return m_lights[name];
    }

    /**
     * Removes a named light source from the manager
     * WARNING: use upload() with every shader to the lights are uploaded to to update all uniforms with new indexes
     * @param name - name of light source to be deleted
     */
    void remove(std::string &name) {
        if(m_lights.count(name)) {
            m_totalLights--;
            m_lights.erase(name);
        }
    }
};

#endif //PROG2002_LIGHTS_H
