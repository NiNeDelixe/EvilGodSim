#include "enginecore/core/ecs/systems/ThirdPersonSystem.h"

void ThirdPersonSystem::update(EntityRegistry<DefaultEntityIndentifier>& registry)
{
    const auto& player_view = registry.template view<ModelComponent, Transform>();

    for (const auto& player_entity : player_view)
    {
        auto& player_transform = player_view.template get<Transform>(player_entity);

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

        if (EngiApp->window()->events()->getScroll() < 0)
        {
            m_camera_distance = glm::clamp(m_camera_distance - m_zoom_speed, 
                                        m_min_camera_distance, m_max_camera_distance);
        }
        if (EngiApp->window()->events()->getScroll() > 0)
        {
            m_camera_distance = glm::clamp(m_camera_distance + m_zoom_speed, 
                                        m_min_camera_distance, m_max_camera_distance);
        }

        if (glm::length(movement) > 0.0f)
        {
            player_transform.m_pos += movement * Time::deltaTime();
        }

        const auto& camera_view = registry.template view<Camera, Transform>();

        for (const auto& camera_entity : camera_view)
        {
            auto& camera = camera_view.template get<Camera>(camera_entity);
            auto& camera_transform = camera_view.template get<Transform>(camera_entity);

            glm::vec3 desired_camera_pos = player_transform.m_pos;
            desired_camera_pos -= player_transform.m_front * m_camera_distance;
            desired_camera_pos.y += m_camera_height;

            camera_transform.m_pos = glm::mix(camera_transform.m_pos, desired_camera_pos, m_smooth_factor);

            glm::vec3 look_direction = glm::normalize(player_transform.m_pos - camera_transform.m_pos);
            
            camera_transform.m_front = glm::mix(
                camera_transform.m_front, 
                look_direction, 
                m_smooth_factor
            );

            camera_transform.m_front_modified = true;

            camera.updateVectors();
            camera_transform.normalizeVectors();
            player_transform.normalizeVectors();
        }
    }
}
