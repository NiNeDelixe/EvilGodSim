#include "enginecore/core/ecs/systems/ThirdPersonSystem.h"



void ThirdPersonSystem::update(EntityRegistry<DefaultEntityIndentifier>& registry)
{
    const auto& player_view = registry.view<ModelComponent, Transform>();

    for (const auto& player_entity : player_view)
    {
        auto& player_transform = player_view.get<Transform>(player_entity);

        glm::dvec3 movement(0.0f);

        if (EngiApp->window()->events()->pressed(Keycode::W))
        {
            movement += player_transform.m_front * m_move_speed;
        }
        if (EngiApp->window()->events()->pressed(Keycode::S))
        {
            movement -= player_transform.m_front * m_move_speed;
        }
        if (EngiApp->window()->events()->pressed(Keycode::A))
        {
            movement -= glm::normalize(glm::cross(player_transform.m_front, player_transform.m_up)) * m_move_speed;
        }
        if (EngiApp->window()->events()->pressed(Keycode::D))
        {
            movement += glm::normalize(glm::cross(player_transform.m_front, player_transform.m_up)) * m_move_speed;
        }

        if (glm::length(movement) > 0.0f)
        {
            player_transform.m_pos += movement * Time::deltaTime();
        }

        const auto& camera_view = registry.view<Camera, Transform>();

        for (const auto& camera_entity : camera_view)
        {
            auto& camera = camera_view.get<Camera>(camera_entity);
            auto& camera_transform = camera_view.get<Transform>(camera_entity);

            glm::fixvec3 camera_pos = player_transform.m_pos;
            camera_pos -= player_transform.m_front * m_camera_distance;
            camera_pos.y += m_camera_height;

            camera_transform.m_pos = glm::mix(camera_transform.m_pos, camera_pos, m_smooth_factor);

            camera_transform.m_front = glm::normalize(player_transform.m_pos - camera_transform.m_pos);

            camera.updateVectors();
        }
    }
}
