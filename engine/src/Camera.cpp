#include "enginecore/core/ecs/entities/Camera.h"

#include "enginecore/core/EngineCoreApplication.h" //FIXME: remove

Camera::Camera(const glm::vec3& position, const float& fov, const entt::entity& entity)
    : m_fov(fov), m_transform(EngiApp->getEntityRegistry().get<Transform>(entity))
{
    m_transform.m_pos = position;
    updateVectors();
}

void Camera::updateVectors()
{
   /* glm::quat rotation = glm::quat_cast(m_transform.m_rotation);
    glm::vec3 front{};
    front.x = std::cos(glm::yaw(rotation)) * std::cos(glm::pitch(rotation));
    front.y = std::sin(glm::pitch(rotation));
    front.z = std::sin(glm::yaw(rotation)) * std::cos(glm::pitch(rotation));
    m_transform.m_front = glm::normalize(front);

    m_transform.m_right = glm::normalize(glm::cross(m_transform.m_front, glm::vec3(0, 1, 0)));
    m_transform.m_up = glm::normalize(glm::cross(m_transform.m_right, m_transform.m_front));*/

    m_transform.m_front = glm::vec3(m_transform.m_rotation * glm::vec4(0, 0, -1, 1));
    m_transform.m_right = glm::vec3(m_transform.m_rotation * glm::vec4(1, 0, 0, 1));
    m_transform.m_up = glm::vec3(m_transform.m_rotation * glm::vec4(0, 1, 0, 1));
    m_transform.m_direction = glm::vec3(m_transform.m_rotation * glm::vec4(0, 0, -1, 1));
    m_transform.m_direction.y = 0;
    float len = glm::length(m_transform.m_direction);
    if (len > 0.0f) 
    {
        m_transform.m_direction.x /= len;
        m_transform.m_direction.z /= len;
    }
}

void Camera::rotate(const float& x, const float& y, const float& z)
{
    m_transform.m_rotation = glm::rotate(m_transform.m_rotation, y, glm::vec3(0, 1, 0));
    m_transform.m_rotation = glm::rotate(m_transform.m_rotation, x, glm::vec3(1, 0, 0));
    m_transform.m_rotation = glm::rotate(m_transform.m_rotation, z, glm::vec3(0, 0, 1));
    /*m_transform.m_yaw += x;
    m_transform.m_pitch += y;
    m_transform.m_roll += z;
    m_transform.m_rotation = glm::mat4_cast(glm::quat(glm::vec3(m_transform.m_pitch, m_transform.m_yaw, m_transform.m_roll)));*/
    updateVectors();
}

glm::mat4 Camera::getProjection() const
{
    if (m_perspective) 
    {
        return glm::perspective(m_fov * m_zoom, m_aspect, m_near, m_far);
    }
    else if (m_flipped)
    {
        return glm::ortho(0.0f, m_fov * m_aspect, m_fov, 0.0f);
    }
    else 
    {
        return glm::ortho(0.0f, m_fov * m_aspect, 0.0f, m_fov);
    }
}

glm::mat4 Camera::getView(const bool& position) const
{
    glm::vec3 camera_pos = m_transform.m_pos;
    if (!position)
    {
        camera_pos = glm::vec3(0.0f);
    }
    if (m_perspective)
    {
        return glm::lookAt(camera_pos, camera_pos + m_transform.m_front, m_transform.m_up);
    }
    else 
    {
        return glm::translate(glm::mat4(1.0f), camera_pos);
    }
}

const float& Camera::getAspectRatio() const
{
	return m_aspect;
}