#include "enginecore/core/ecs/systems/CameraSystem.h"

void CameraSystem::update(entt::registry& registry)
{
	const auto& camera_view = registry.view<Camera, Transform>();
	for (const auto& entity : camera_view)
	{
		auto& camera = camera_view.get<Camera>(entity);
	}
}