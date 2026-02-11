#include "enginecore/core/ecs/systems/RotationSystem.h"

void RotationSystem::update(EntityRegistry<DefaultEntityIndentifier> &registry)
{
    const auto& rotation_view = registry.view<Transform>(); 

    for(auto&& [rotation_entity, rotation_component] : rotation_view.each())
    {
        glm::extractEulerAngleYXZ(rotation_component.m_rotation, 
            rotation_component.m_yaw, rotation_component.m_pitch, rotation_component.m_roll);
    }
}