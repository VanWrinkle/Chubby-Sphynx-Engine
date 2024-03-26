#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include "camera/camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <array>

const float RAD_TO_DEGREES = 180.0f / M_PI;
const float DEG_TO_RADIANS = M_PI / 180.f;

class PerspectiveCamera : public Camera
{
public:
    struct Frustum {
        float angle;
        float width;
        float height;
        float near;
        float far;
    };

public:
    PerspectiveCamera(const Frustum &frustum = {45.0f, -1.0f, 1.0f, 1.0f, -1.0f},
                      const glm::vec3 &position = glm::vec3(5.0f),
                      const glm::vec3 &lookAt = glm::vec3(0.0f),
                      const glm::vec3 &upVector = glm::vec3(0.0f, 1.0f, 0.0f)) {
        m_cameraFrustum = frustum;
        m_position = position;
        m_magnitude = glm::length( lookAt - position);
        m_front = glm::normalize(lookAt - position);
        m_upVector = upVector;
        m_projectionMatrix = glm::perspective(glm::radians(frustum.angle),
                                              static_cast<float>(frustum.width) / frustum.height,
                                              frustum.near,
                                              frustum.far);
        m_viewMatrix = glm::lookAt(position, position + m_front, upVector);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
        m_cameraRight = glm::normalize(glm::cross(m_front, m_upVector));
        m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_front));
        //updateOrientation();
    };

    ~PerspectiveCamera()=default;
/*
    PerspectiveCamera(const PerspectiveCamera &camera): Camera(camera) {
        this->m_lookAt = camera.m_lookAt;
        this->m_upVector = camera.m_upVector;
        this->m_cameraFrustum = camera.m_cameraFrustum;
        updateVectors();
    }
*/
    /**
     * Moves relative to the cameras local coordinate
     * @param direction - direction given as camera local coordinates
     * @param deltaTime
     * @param normalize
     */
    void move(glm::vec3 direction , float magnitude) {

        m_position += magnitude * direction.x * m_cameraRight;
        m_position += magnitude * direction.y * m_cameraUp;
        m_position += magnitude * direction.z * m_front;

        this->recalculateMatrix();
    }



    void setPosition(const glm::vec3& pos) override {
        glm::vec3 direction = m_magnitude * m_front + m_position - pos;
        m_magnitude = glm::length(direction);
        m_front = direction/m_magnitude;
        updateOrientation();
        Camera::setPosition(pos);
    }

    void SetFrustum(const Frustum& frustum) {
        this->m_cameraFrustum = frustum; this->recalculateMatrix();
    }

    void SetLookAt(const glm::vec3& lookAt) {
        glm::vec3 direction = lookAt - m_position;
        m_magnitude = glm::length(direction);
        m_front = direction/m_magnitude;
        updateOrientation();
        this->recalculateMatrix();
    }

    void SetUpVector(const glm::vec3& upVector) {
        this->m_upVector = upVector; this->recalculateMatrix();
        updateOrientation();
    }

    void mouseInput( const glm::vec2 &delta ) {
        m_yaw += delta.x;
        m_pitch = std::max( std::min(m_pitch - delta.y, 89.0f), -89.0f);
        updateFrontFromOrientation();
        recalculateOrthogonals();
        this->recalculateMatrix();
    }

protected:
    void recalculateMatrix() override {
        m_projectionMatrix = glm::perspective(glm::radians(m_cameraFrustum.angle),
                                              static_cast<float>(m_cameraFrustum.width) / m_cameraFrustum.height,
                                              m_cameraFrustum.near,
                                              m_cameraFrustum.far);
        m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_upVector);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    };

    void updateFrontFromOrientation() {
        m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front.y = sin(glm::radians(m_pitch));
        m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    }

    void recalculateOrthogonals() {
        m_cameraRight = glm::normalize(glm::cross(m_front, m_upVector));
        m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_front));
    }

    void updateOrientation() {
        m_pitch = glm::degrees(asinf(m_front.y));
        float x = m_front.x / cos(glm::radians(m_pitch));
        float z = m_front.z / cos(glm::radians(m_pitch));
        m_yaw = glm::degrees(atan2f(z, x));
    }





protected:
    float m_magnitude;
    glm::vec3 m_upVector;
    glm::vec3 m_cameraUp;
    glm::vec3 m_cameraRight;
    glm::vec3 m_front;
    float m_yaw             {-90.0f};
    float m_pitch           {};
    Frustum m_cameraFrustum;
};

#endif // PERSPECTIVECAMERA_H_
