#pragma once
#ifndef SYSTEMS_CAMERASYSTEM_H_
#define SYSTEMS_CAMERASYSTEM_H_

#include "enginecore/interfaces/ISystem.h"

#include "enginecore/core/ecs/entities/Camera.h"
#include "enginecore/core/ecs/components/Transform.h"

class CameraSystem : public ISystem
{
public:
	CameraSystem() = default;
	~CameraSystem() = default;

	void update(entt::registry& registry) override;

private:

};


#endif // !SYSTEMS_CAMERASYSTEM_H_