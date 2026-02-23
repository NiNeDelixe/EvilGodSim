#pragma once
#ifndef PHYSICS_RIGIDBODY_H_
#define PHYSICS_RIGIDBODY_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/core/LibrariesDefines.h"

#include "enginecore/core/physics/Hitbox.h"

class Rigidbody
{
public:
    Rigidbody(const entt::entity& entity);
    ~Rigidbody() = default;

public:
    GETTER(bool, m_enabled, Enabled)
    SETTER(bool, m_enabled, Enabled)
    
    GETTER(Hitbox, m_hitbox, Hitbox)
    SETTER(Hitbox, m_hitbox, Hitbox)

    GETTER(std::vector<Sensor>, m_sensors, Sensors)
    SETTER(std::vector<Sensor>, m_sensors, Sensors)

private:
    bool m_enabled = true;
    Hitbox m_hitbox;
    std::vector<Sensor> m_sensors;
};

#endif  // PHYSICS_RIGIDBODY_H_
