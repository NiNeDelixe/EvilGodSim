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
};


#endif // !COMPONENTS_ROTATION_H_