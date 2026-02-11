#include "PlayerControllSystem.h"

void PlayerControllSystem::update(EntityRegistry<DefaultEntityIndentifier> &registry)
{
    const auto& player_view = registry.template view<ModelComponent, Transform, PlayerComponent>();

    for (const auto& [player_entity, model_c, player_transform, player_c] : player_view.each())
    {
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
            glm::vec3 move_direction = glm::normalize(movement);
                
            player_transform.m_rotation = glm::inverse(glm::lookAt(glm::vec3(0.0f), move_direction, player_transform.m_up)) * m_move_speed;
            
            player_transform.m_pos += movement * Time::deltaTime();
        }
    }
}