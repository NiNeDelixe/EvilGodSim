#pragma once
#ifndef ENTITIES_CAMERA_H_
#define ENTITIES_CAMERA_H_

#include <memory>
#include <cmath>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <entt/entt.hpp>

#include "enginecore/core/window/Viewport.h"

#include "enginecore/interfaces/IEntity.h"

#include "enginecore/core/ecs/components/transform/Transform.h"

class Camera : public IEntity
{
public:
    Camera() = default;
    Camera(const glm::vec3& position, const float& fov, const entt::entity& entity);

    void updateVectors();
    void rotate(const float& x, const float& y, const float& z);
    void rotate(const glm::vec3& vec) { rotate(vec.x, vec.y, vec.z); }

    void lookAt(const glm::vec3& target);
    void lookAt(const glm::vec3& target, const float& interpolation);

    glm::mat4 getProjection() const;
    glm::mat4 getView(const bool& position = true) const;

    void setFov(const float& fov) 
    { 
        this->m_fov = fov; 
    }
    const float& getFov() const 
    { 
        return this->m_fov; 
    }

    const float& getAspectRatio() const;
    void setAspectRatio(const float& ratio) 
    { 
        m_aspect = ratio; 
    }

public:
    float m_fov = 1.0f;
    Transform& m_transform;

private:
    //CameraTransform m_camera_data;

private:
    float m_zoom = 1.0f;
    bool m_perspective = true;
    bool m_flipped = false;
    float m_aspect = 0.0f;
    float m_near = 0.05f;
    float m_far = 1e4f;
};

#endif // !ENTITIES_CAMERA_H_

