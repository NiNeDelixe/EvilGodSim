#pragma once
#ifndef COMPONENTS_ROTATION_H_
#define COMPONENTS_ROTATION_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "enginecore/interfaces/IComponent.h"

class Rotation : public IComponent
{
public:
	glm::mat4 m_rotation{ 1.0f };

	float m_yaw;
	float m_pitch;
	float m_roll;
};


#endif // !COMPONENTS_ROTATION_H_