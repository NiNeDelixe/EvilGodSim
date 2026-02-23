#include "enginecore/core/ecs/systems/ThirdPersonSystem.h"

ThirdPersonSystem::ThirdPersonSystem()
    : ISystem(SystemCategory::CAMERA_BEHAVIOR)
{
}

void ThirdPersonSystem::update(EntityRegistry<DefaultEntityIndentifier> &registry)
{
    const auto& player_view = registry.template view<ModelComponent, Transform, PlayerComponent>();
    const auto& camera_view = registry.template view<Camera, Transform>();

    for (auto&& [player_entity, model_c, player_transform, player_c] : player_view.each())
    {
        if (EngiApp->window()->events()->getScroll() > 0)
        {
            m_camera_distance = glm::clamp(m_camera_distance - m_zoom_speed, 
                                        m_min_camera_distance, m_max_camera_distance);
        }
        if (EngiApp->window()->events()->getScroll() < 0)
        {
            m_camera_distance = glm::clamp(m_camera_distance + m_zoom_speed, 
                                        m_min_camera_distance, m_max_camera_distance);
        }

        for (auto&& [camera_entity, camera, camera_transform] : camera_view.each())
        {
            // camera_transform.m_rotation = glm::translate(camera_transform.m_rotation, {0.f, m_camera_distance, m_camera_distance}) *
            //     glm::rotate(camera_transform.m_pitch, camera_transform.m_yaw, 0.f) *
            //     glm::translate(player_transform.m_pos.x, player_transform.m_pos.y, player_transform.m_pos.z);

            // glm::vec3 offset(0, 3, 20);
            // glm::vec3 cp = glm::rotate(glm::vec3(0.f, 0.f, m_camera_distance), camera_transform.m_yaw, glm::vec3(0, 1, 0));

            // camera_transform.m_pos = player_transform.m_pos + cp + offset;
            
            
            glm::vec3 desired_camera_pos = player_transform.m_pos;
            desired_camera_pos -= player_transform.m_front * m_camera_distance;
            desired_camera_pos.y += m_camera_height;
            
            camera_transform.m_pos = glm::mix(camera_transform.m_pos, desired_camera_pos, m_smooth_factor);
            
            camera.lookAt(player_transform.m_pos);

            // glm::vec3 look_direction = glm::normalize(player_transform.m_pos - camera_transform.m_pos);
            
            // camera_transform.m_front = glm::mix(
            //     camera_transform.m_front, 
            //     look_direction, 
            //     m_smooth_factor
            // );

            // camera_transform.m_front_modified = true;

            camera.updateVectors();
        }
    }
}
