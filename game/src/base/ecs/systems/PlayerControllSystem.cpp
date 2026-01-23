#include "PlayerControllSystem.h"

void PlayerControllSystem::update(EntityRegistry<DefaultEntityIndentifier> &registry)
{
    const auto& player_view = registry.template view<ModelComponent, Transform>();

    for (const auto& player_entity : player_view)
    {
        auto& player_transform = player_view.template get<Transform>(player_entity);

        glm::dvec3 movement(0.0f);
        glm::dvec3 move_direction(0.0f);

        if (EngiApp->window()->events()->pressed(Keycode::W))
        {
            movement += player_transform.m_front * m_move_speed;
            move_direction += glm::vec3(0, 0, -1);
        }
        if (EngiApp->window()->events()->pressed(Keycode::S))
        {
            movement -= player_transform.m_front * m_move_speed;
            move_direction += glm::vec3(0, 0, 1);
        }
        if (EngiApp->window()->events()->pressed(Keycode::A))
        {
            movement -= glm::normalize(glm::cross(player_transform.m_front, player_transform.m_up)) * m_move_speed;
            move_direction += glm::vec3(-1, 0, 0);
        }
        if (EngiApp->window()->events()->pressed(Keycode::D))
        {
            movement += glm::normalize(glm::cross(player_transform.m_front, player_transform.m_up)) * m_move_speed;
            move_direction += glm::vec3(1, 0, 0);
        }

        if (glm::length(movement) > 0.0f)
        {            
            glm::vec3 move_direction = glm::normalize(movement);
                
            player_transform.m_rotation = glm::inverse(glm::lookAt(glm::vec3(0.0f), move_direction, player_transform.m_up));

            player_transform.normalizeVectors();


            player_transform.m_pos += movement * Time::deltaTime();
        }
    }
}