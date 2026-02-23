#include "enginecore/core/ecs/systems/TransformSystem.h"

TransformSystem::TransformSystem()
    : ISystem(SystemCategory::TRANSFORM)
{
}

void TransformSystem::update(EntityRegistry<DefaultEntityIndentifier> &registry)
{
    const auto& transform_view = registry.view<Transform>();

    for(auto&& [transform_entity, transform_component] : transform_view.each())
    {
        if (glm::length(transform_component.m_front) < 0.001f) 
            transform_component.m_front = glm::vec3(0, 0, 1);
        if (glm::length(transform_component.m_up) < 0.001f) 
            transform_component.m_up = glm::vec3(0, 1, 0);
        transform_component.m_front = glm::normalize(transform_component.m_front);
        transform_component.m_up = glm::normalize(transform_component.m_up);

        if (transform_component.m_front_modified)
        {
            transform_component.m_front_modified = false;
            glm::vec3 front = glm::normalize(transform_component.m_front);
            glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 right = glm::normalize(glm::cross(front, world_up));
            glm::vec3 up = glm::normalize(glm::cross(right, front));
            
            transform_component.m_rotation = glm::mat4(
                glm::vec4(right, 0.0f),
                glm::vec4(up, 0.0f),
                glm::vec4(-front, 0.0f), // OpenGL front = -z
                glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
            );
        }
        else
        {
            transform_component.m_front = glm::vec3(transform_component.m_rotation * glm::vec4(0, 0, -1, 1));
            transform_component.m_right = glm::vec3(transform_component.m_rotation * glm::vec4(1, 0, 0, 1));
            transform_component.m_up = glm::vec3(transform_component.m_rotation * glm::vec4(0, 1, 0, 1));
            transform_component.m_direction = glm::vec3(transform_component.m_rotation * glm::vec4(0, 0, -1, 1));
            transform_component.m_direction.y = 0;
            float len = glm::length(transform_component.m_direction);
            if (len > 0.0f) 
            {
                transform_component.m_direction.x /= len;
                transform_component.m_direction.z /= len;
            }
        }
    }
}