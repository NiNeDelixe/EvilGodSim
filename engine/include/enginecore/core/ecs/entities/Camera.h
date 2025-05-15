#pragma once
#ifndef ENTITIES_CAMERA_H_
#define ENTITIES_CAMERA_H_

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "enginecore/core/window/Viewport.h"

#include "enginecore/interfaces/IEntity.h"

class Camera : public IEntity
{
public:
    Camera();
    Camera(const glm::vec3& position, const float& fov);

    void updateVectors();
    void rotate(const float& x, const float& y, const float& z);
    void rotate(const glm::vec3& vec) { rotate(vec.x, vec.y, vec.z); }

    glm::mat4 getProjection() const;
    glm::mat4 getView(const bool& position = true) const;

    void setFov(const float& fov) { this->m_fov = fov; }
    const float& getFov() const { return this->m_fov; }

    float getAspectRatio() const;

public:
    float m_fov = 1.0f;
    std::weak_ptr<Viewport> m_viewport;

public:
    float m_zoom = 1.0f;
    bool m_perspective = true;
    bool m_flipped = false;
    float m_aspect = 0.0f;
    float m_near = 0.05f;
    float m_far = 1500.0f;
};

#endif // !ENTITIES_CAMERA_H_

