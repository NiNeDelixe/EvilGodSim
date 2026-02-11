#pragma once
#ifndef COMPONENTS_ROTATION_H_
#define COMPONENTS_ROTATION_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include "enginecore/interfaces/IComponent.h"

class Rotation : public IComponent
{
public:
	glm::mat4 m_rotation{ 1.0f };

	float m_yaw = .0f;
	float m_pitch = .0f;
	float m_roll = .0f;
};


#endif // !COMPONENTS_ROTATION_H_