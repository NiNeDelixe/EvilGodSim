#pragma once
#ifndef SYSTEMS_THIRDPERSONSYSTEM_H_
#define SYSTEMS_THIRDPERSONSYSTEM_H_

#include "enginecore/core/CoreDefines.h"

#include <glm/common.hpp>
#include <glm/glm.hpp>

#include "enginecore/core/EngineCoreApplication.h"
#include "enginecore/core/Time.h"

#include "enginecore/core/ecs/components/ModelComponent.h"

#include "enginecore/interfaces/ISystem.h"

#include "enginecore/core/window/Input.h"

class ThirdPersonSystem : public ISystem
{
public:
	ThirdPersonSystem() = default;
	~ThirdPersonSystem() = default;

public:
	void update(EntityRegistry<DefaultEntityIndentifier>& registry) override;

private:
    float m_move_speed = 3.0f;
    float m_rotation_speed = 2.0f;
    float m_camera_distance = 5.0f;
    float m_camera_height = 2.0f;
    float m_min_camera_distance = 2.0f;
    float m_max_camera_distance = 10.0f;
    float m_zoom_speed = 0.5f;

    glm::vec3 m_current_camera_offset{};
    float m_smooth_factor = 0.1f;
};

#endif // !SYSTEMS_THIRDPERSONSYSTEM_H_