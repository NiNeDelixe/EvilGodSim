#pragma once
#ifndef COMPONENTS_SIZE_H_
#define COMPONENTS_SIZE_H_

#include "enginecore/core/CoreDefines.h"

#include <glm/glm.hpp>

#include "enginecore/interfaces/IComponent.h"

class Size : public IComponent
{
public:
	glm::vec3 m_size{ 1.f };

};

#endif // !COMPONENTS_SIZE_H_