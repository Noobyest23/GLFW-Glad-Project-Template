#include "camera.h"

Camera::Camera(float aspectRatio, float fovDeg, float nearPlane, float farPlane)
    : rotation(0.0f), fov(glm::radians(fovDeg)),
    aspect(aspectRatio), nearClip(nearPlane), farClip(farPlane) {}

glm::vec3 Camera::GetForward() const {
    glm::vec3 rotRad = glm::radians(rotation);
    return glm::normalize(glm::vec3(
        cos(rotRad.y) * cos(rotRad.x),
        sin(rotRad.x),
        sin(rotRad.y) * cos(rotRad.x)
    ));
}

glm::mat4 Camera::GetViewMatrix() const {
    glm::vec3 forward = GetForward();
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return glm::perspective(fov, aspect, nearClip, farClip);
}
