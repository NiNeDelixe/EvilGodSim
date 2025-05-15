#include "enginecore/core/ecs/entities/Camera.h"

Camera::Camera()
{
}

Camera::Camera(const glm::vec3& position, const float& fov)
{
}

void Camera::updateVectors()
{
}

void Camera::rotate(const float& x, const float& y, const float& z)
{
}

glm::mat4 Camera::getProjection() const
{
	return glm::mat4();
}

glm::mat4 Camera::getView(const bool& position) const
{
	return glm::mat4();
}

float Camera::getAspectRatio() const
{
	return 0.0f;
}