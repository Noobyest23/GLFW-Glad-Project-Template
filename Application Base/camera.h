#ifndef NAPP_CAMERA
#define NAPP_CAMERA
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

class Camera {
public:
	Camera(float aspectRatio, float fovDeg = 60.0f, float nearPlane = 0.1f, float farPlane = 1000.0f);

	glm::vec3 GetForward() const;

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);

private:
	float fov, aspect, nearClip, farClip;
};

#endif