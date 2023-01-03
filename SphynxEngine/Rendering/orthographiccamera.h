//
// Created by andre on 19.11.22.
//

#ifndef ORTHOGRAPHICCAMERA_H_
#define ORTHOGRAPHICCAMERA_H_

#include <camera.h>

#include <glm/fwd.hpp>

#include <array>

class OrthographicCamera : public Camera
{
public:

    struct Frustum {
        float left;
        float right;
        float bottom;
        float top;
        float near;
        float far;
    };

public:
    explicit OrthographicCamera(const Frustum& frustum={-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f},
                       const glm::vec3& position=glm::vec3(0.0f), float rotation=0.0f) {
        m_position = position;
        m_rotation = rotation;
        m_projectionMatrix = glm::ortho(frustum.left, frustum.right, frustum.bottom,
                                        frustum.top, frustum.near, frustum.far);
        m_viewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        m_viewMatrix = glm::translate(m_viewMatrix, position);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    };
    ~OrthographicCamera()=default;

    OrthographicCamera(const OrthographicCamera& camera) : Camera(camera) {
        this->m_rotation = camera.m_rotation;
        this->m_cameraFrustum = camera.m_cameraFrustum;
    }

    void SetRotation(float rotation) {
        this->m_rotation = rotation;
        this->recalculateMatrix();
    }

    void SetFrustrum(const Frustum& frustrum) {
        this->m_cameraFrustum =frustrum;
        this->recalculateMatrix();
    }

protected:
    void recalculateMatrix() override {
        m_projectionMatrix = glm::ortho(m_cameraFrustum.left, m_cameraFrustum.right, m_cameraFrustum.bottom,
                                        m_cameraFrustum.top, m_cameraFrustum.near, m_cameraFrustum.far);
        m_viewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        m_viewMatrix = glm::translate(m_viewMatrix, m_position);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    };

protected:
    float m_rotation; // in degrees around the Z axis
    Frustum m_cameraFrustum{};
};

#endif // ORTHOGRAPHICCAMERA_H_
