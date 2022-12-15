//
// Created by anmar on 10/1/2022.
//

#ifndef PROG2002_MODELMATRIX_H
#define PROG2002_MODELMATRIX_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Encapsulates operations to transform an object globally or locally
 */
class ModelMatrix {
private:
    glm::mat4 m_rotation {1};
    glm::mat4 m_translation {1};
    glm::mat4 m_scale {1};
    glm::vec3 m_position {};

public:
    ModelMatrix() = default;


    inline void rotateLocal(const float &degrees, const glm::vec3 &axis){
        m_rotation = glm::rotate(m_rotation, glm::radians(degrees), axis);
    };


    inline void rotateGlobal(const float &degrees, const glm::vec3 &axis) {
        m_rotation = glm::rotate(m_rotation, glm::radians(degrees), glm::inverse(glm::mat3(m_rotation))*axis);
    }


    inline void setRotation(const float &degrees, const glm::vec3 &axis){
        m_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), axis);
    };


    inline void move(const glm::vec3 &translation) {
        m_position += translation;
        m_translation = glm::translate(m_translation, translation);
    };


    inline void setPosition(const glm::vec3 &position) {
        m_position = position;
        m_translation = glm::translate(glm::mat4(1.0f), position);
    };


    inline void scale(const glm::vec3 &scale)  {
        m_scale = glm::scale(m_scale, scale);
    };


    inline void setScale(const glm::vec3 &scale) {
        m_scale = glm::scale(glm::mat4(1.0f), scale);
    };


    [[nodiscard]] inline glm::vec3 getPosition() const {
        return m_position;
    }


    [[nodiscard]] inline glm::mat4 getMatrix() const {
        return m_translation * m_rotation * m_scale;
    }


    [[nodiscard]] inline glm::mat3 getNormalMatrix() const {
        return (glm::transpose(glm::inverse(glm::mat3(m_translation * m_rotation * m_scale))));
    }




};

#endif //PROG2002_MODELMATRIX_H
