#include "enginecore/core/EngineCoreApplication.h"
#include "enginecore/core/ecs/systems/FreeFlySystem.h"


void FreeFlySystem::update(EntityRegistry<DefaultEntityIndentifier>& registry)
{
	const auto& transform_view = registry.view<Camera, Transform>();
	for (const auto& entity : transform_view)
	{
		auto& transform = transform_view.get<Transform>(entity);
		auto& camera = transform_view.get<Camera>(entity);		
		
		if (EngiApp->window()->events()->pressed(Keycode::W))
		{
			transform.m_pos += transform.m_front * m_speed;
		}
		if (EngiApp->window()->events()->pressed(Keycode::S))
		{
			transform.m_pos -= transform.m_front * m_speed;
		}
		if (EngiApp->window()->events()->pressed(Keycode::A))
		{
			transform.m_pos -= glm::normalize(glm::cross(transform.m_front, transform.m_up)) * m_speed;
		}
		if (EngiApp->window()->events()->pressed(Keycode::D))
		{
			transform.m_pos += glm::normalize(glm::cross(transform.m_front, transform.m_up)) * m_speed;
		}
		if (EngiApp->window()->events()->pressed(Keycode::LEFT_SHIFT))
		{
			transform.m_pos -= transform.m_up * m_speed;
		}
		if (EngiApp->window()->events()->pressed(Keycode::SPACE))
		{
			transform.m_pos += transform.m_up * m_speed;
		}

		if (EngiApp->window()->events()->pressed(Keycode::UP))
		{
			rotation.y += m_rotation_speed;
		}
		if (EngiApp->window()->events()->pressed(Keycode::DOWN))
		{
			rotation.y -= m_rotation_speed;
		}
		if (EngiApp->window()->events()->pressed(Keycode::LEFT))
		{
			rotation.x += m_rotation_speed;
		}
		if (EngiApp->window()->events()->pressed(Keycode::RIGHT))
		{
			rotation.x -= m_rotation_speed;
		}

		float sensitivity = EngiApp->getGlobalSettings()->camera()->sensitivity.get();
		glm::vec2 cusror_delta = EngiApp->window()->events()->getCursorDelta();

		auto d = glm::degrees(
			cusror_delta / static_cast<float>(EngiApp->window()->viewports()[0]->getHeight()) * sensitivity);
		rotation.x -= d.x;
		rotation.y -= d.y;

		if (rotation.y < -89.9f) 
		{
			rotation.y = -89.9f;
		}
		else if (rotation.y > 89.9f) 
		{
			rotation.y = 89.9f;
		}
		if (rotation.x > 180.f) 
		{
			rotation.x -= 360.f;
		}
		else if (rotation.x < -180.f) 
		{
			rotation.x += 360.f;
		}

		transform.m_rotation = glm::mat4(1);
		camera.rotate(glm::radians(rotation.y),
			glm::radians(rotation.x), glm::radians(rotation.z));

		camera.updateVectors();
	}
}