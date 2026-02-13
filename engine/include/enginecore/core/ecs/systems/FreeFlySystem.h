#pragma once
#ifndef SYSTEMS_FREEFLYSYSTEM_H_
#define SYSTEMS_FREEFLYSYSTEM_H_

#include "enginecore/interfaces/ISystem.h"

#include "enginecore/core/ecs/components/transform/Transform.h"

#include "enginecore/core/window/Input.h"

class FreeFlySystem : public ISystem
{
public:
	FreeFlySystem() = default;
	~FreeFlySystem() = default;

	void update(EntityRegistry<DefaultEntityIndentifier>& registry) override;

private:
	float m_speed = 1;
	float m_rotation_speed = 1;
	glm::vec3 rotation{};
};


#endif // !SYSTEMS_FREEFLYSYSTEM_H_