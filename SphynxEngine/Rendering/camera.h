//
// Created by andre on 19.11.22.
//

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera()=default;
    ~Camera()=default;

    // Get camera matrices
    [[nodiscard]] const glm::mat4& getProjectionMatrix() const {
        return this->m_projectionMatrix;
    }

    [[nodiscard]] const glm::mat4& getViewMatrix() const {
        return this->m_viewMatrix; }

    [[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const {
        return this->m_viewProjectionMatrix;
    }

    // Set/Get position
    [[nodiscard]] const glm::vec3& getPosition() const {
        return this->m_position;
    }

    virtual void setPosition(const glm::vec3& pos) {
        this->m_position = pos;
        this->recalculateMatrix();
    }

protected:
    virtual void recalculateMatrix() = 0;

protected:
    Camera(const Camera& camera)
    {
        this->m_projectionMatrix = camera.m_projectionMatrix;
        this->m_viewMatrix = camera.m_viewMatrix;
        this->m_position = camera.m_position;
        this->m_viewProjectionMatrix = camera.m_viewProjectionMatrix;
    }

protected:
    glm::vec3 m_orientation;
    glm::mat4 m_projectionMatrix = glm::mat4(1.0f);
    glm::mat4 m_viewMatrix = glm::mat4(1.0f);
    glm::mat4 m_viewProjectionMatrix = glm::mat4(1.0f);
    glm::vec3 m_position = glm::vec3(0.0f);
};

#endif // CAMERA_H_

