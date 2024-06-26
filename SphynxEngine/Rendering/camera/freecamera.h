//
// Created by anmar on 10/1/2022.
//

#ifndef PROG2002_FREECAMERA_H
#define PROG2002_FREECAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class FreeCamera {
public:
    glm::vec3 m_position    {0.0f, 0.0f, 0.0f};
    glm::vec3 m_front       {0.0f, 0.0f, -1.0f}; ///< unit vector from position to target. position + front = target/lookAt
    glm::vec3 m_cameraUp    {0.0f, 1.0f, 0.0f};
    glm::vec3 m_cameraRight {1.0f, 0.0f, 0.0f};
    float m_yaw             {-90.0f};
    float m_pitch           {};


    void updateVectors() {

        m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front.y = sin(glm::radians(m_pitch));
        m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(m_front);

        m_cameraRight = glm::normalize(glm::cross(m_front, {0.0f, 1.0f, 0.0f}));
        m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_front));
    }

public:

    FreeCamera() = default;

    /**
     * Moves relative to the cameras local coordinate
     * @param direction - direction given as camera local coordinates
     * @param deltaTime
     * @param normalize
     */
    void move(glm::vec3 direction , float magnitude, bool normalize = false) {
        if(normalize) {
            direction = glm::normalize(direction);
        }

        m_position += magnitude * direction.x * m_cameraRight;
        m_position += magnitude * direction.y * m_front;
        m_position += magnitude * direction.z * m_cameraUp;
        updateVectors();
    }


    void mouseInput(float dX, float dY){
        m_yaw += dX;
        m_pitch = std::max( std::min(m_pitch + dX, 89.0f), -89.0f);
        updateVectors();
    }

    void mouseInput( const glm::vec2 &delta ) {
        m_yaw += delta.x;
        m_pitch = std::max( std::min(m_pitch - delta.y, 89.0f), -89.0f);
        updateVectors();
    }


    glm::mat4 getView() const {
        // position, target position, up
        return glm::lookAt(m_position, m_position + m_front, m_cameraUp);
    }

    [[nodiscard]] glm::vec3 getPosition() const {
        return m_position;
    }
};




#endif //PROG2002_FREECAMERA_H
