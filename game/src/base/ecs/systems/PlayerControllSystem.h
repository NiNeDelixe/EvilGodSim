#pragma once
#ifndef SYSTEMS_PLAYERCONTROLLSYSTEM_H_
#define SYSTEMS_PLAYERCONTROLLSYSTEM_H_

#include <enginecore/core/CoreDefines.h>

#include <glm/common.hpp>
#include <glm/glm.hpp>

#include <enginecore/core/EngineCoreApplication.h>
#include <enginecore/core/Time.h>

#include <enginecore/core/ecs/components/ModelComponent.h>
#include <enginecore/core/ecs/components/PlayerComponent.h>

#include <enginecore/interfaces/ISystem.h>
#include <enginecore/core/window/Input.h>

class PlayerControllSystem : public ISystem
{
public:
    PlayerControllSystem() = default;
    ~PlayerControllSystem() = default;

public:
    void update(EntityRegistry<DefaultEntityIndentifier>& registry) override;

private:
    //TODO: move to component
    float m_move_speed = 5.0f;
    float m_rotation_speed = 0.5f;
};

#endif  // SYSTEMS_PLAYERCONTROLLSYSTEM_H_
