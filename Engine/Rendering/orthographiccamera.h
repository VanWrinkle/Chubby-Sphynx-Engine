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

    struct Frustrum {
        float left;
        float right;
        float bottom;
        float top;
        float near;
        float far;
    };

public:
    explicit OrthographicCamera(const Frustrum& frustrum={-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f},
                       const glm::vec3& position=glm::vec3(0.0f), float rotation=0.0f) {
        Position = position;
        Rotation = rotation;
        ProjectionMatrix = glm::ortho(frustrum.left, frustrum.right, frustrum.bottom,
                                      frustrum.top, frustrum.near, frustrum.far);
        ViewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        ViewMatrix = glm::translate(ViewMatrix, position);
        ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
    };
    ~OrthographicCamera()=default;

    OrthographicCamera(const OrthographicCamera& camera) : Camera(camera) {
        this->Rotation = camera.Rotation;
        this->CameraFrustrum = camera.CameraFrustrum;
    }

    void SetRotation(float rotation) {
        this->Rotation = rotation; this->RecalculateMatrix();
    }

    void SetFrustrum(const Frustrum& frustrum) {
        this->CameraFrustrum =frustrum; this->RecalculateMatrix();
    }

protected:
    void RecalculateMatrix() override {
        ProjectionMatrix = glm::ortho(CameraFrustrum.left, CameraFrustrum.right, CameraFrustrum.bottom,
                                      CameraFrustrum.top, CameraFrustrum.near, CameraFrustrum.far);
        ViewMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        ViewMatrix = glm::translate(ViewMatrix, Position);
        ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
    };

protected:
    float Rotation; // in degrees around the Z axis
    Frustrum CameraFrustrum{};
};

#endif // ORTHOGRAPHICCAMERA_H_
