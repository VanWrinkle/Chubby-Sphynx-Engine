#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include <camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <array>

class PerspectiveCamera : public Camera
{
public:
    struct Frustrum {
        float angle;
        float width;
        float height;
        float near;
        float far;
    };

public:
    PerspectiveCamera(const Frustrum &frustrum = {45.0f, -1.0f, 1.0f, 1.0f, -1.0f},
                      const glm::vec3 &position = glm::vec3(5.0f),
                      const glm::vec3 &lookAt = glm::vec3(0.0f),
                      const glm::vec3 &upVector = glm::vec3(0.0f, 1.0f, 0.0f)) {
        CameraFrustrum = frustrum;
        Position = position;
        LookAt = lookAt;
        UpVector = upVector;
        ProjectionMatrix = glm::perspective(glm::radians(frustrum.angle),
                                            static_cast<float>(frustrum.width)/frustrum.height,
                                            frustrum.near,
                                            frustrum.far);
        ViewMatrix = glm::lookAt(position, lookAt, upVector);
        ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
    };

    ~PerspectiveCamera()=default;

    PerspectiveCamera(const PerspectiveCamera &camera): Camera(camera) {
        this->LookAt = camera.LookAt;
        this->UpVector = camera.UpVector;
        this->CameraFrustrum = camera.CameraFrustrum;
    }

    void SetFrustrum(const Frustrum& frustrum) {
        this->CameraFrustrum = frustrum; this->RecalculateMatrix();
    }

    void SetLookAt(const glm::vec3& lookAt) {
        this->LookAt = lookAt; this->RecalculateMatrix();
    }

    void SetUpVector(const glm::vec3& upVector) {
        this->UpVector = upVector; this->RecalculateMatrix();
    }

protected:
    void RecalculateMatrix() override {
        ProjectionMatrix = glm::perspective(glm::radians(CameraFrustrum.angle),
                                            static_cast<float>(CameraFrustrum.width)/CameraFrustrum.height,
                                            CameraFrustrum.near,
                                            CameraFrustrum.far);
        ViewMatrix = glm::lookAt(Position, LookAt, UpVector);
        ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
    };

protected:
    glm::vec3 LookAt;
    glm::vec3 UpVector;
    Frustrum CameraFrustrum;
};

#endif // PERSPECTIVECAMERA_H_
