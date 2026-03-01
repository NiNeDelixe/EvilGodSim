#pragma once
#ifndef PHYSICS_HITBOX_H_
#define PHYSICS_HITBOX_H_

#include "enginecore/core/CoreDefines.h"

#include <set>
#include <string>
#include <functional>

#include <glm/glm.hpp>

#include "enginecore/utils/math/AABB.h"

enum class SensorType 
{
    AABB,
    RADIUS,
};

union SensorParams 
{
    AABB aabb;
    glm::vec4 radial; // x,y,z calculated entity coords + w - radius

    constexpr SensorParams() : aabb() {}
};

using sensor_callback = std::function<void(entityid_t)>;

struct Sensor 
{
    bool enabled = true;
    SensorType type;
    size_t index;
    entityid_t entity;
    SensorParams params;
    SensorParams calculated;
    std::set<entityid_t> prev_entered;
    std::set<entityid_t> next_entered;
    sensor_callback enter_callback;
    sensor_callback exit_callback;
};

enum class BodyType 
{
    STATIC, 
    KINEMATIC, 
    DYNAMIC
};

class Hitbox 
{
public:
    Hitbox(BodyType type, glm::vec3 position, glm::vec3 halfsize)
        : m_type(type), m_position(position), m_halfsize(halfsize), m_velocity(0.0f,0.0f,0.0f)
    {}

    AABB getAABB() const 
    {
        return AABB(m_position - m_halfsize, m_position + m_halfsize);
    }

    glm::vec3 getHalfSize() const 
    {
        return m_halfsize * m_scale;
    }

public:
    GETTER(BodyType, m_type, Type)
    SETTER(BodyType, m_type, Type)

    GETTER(glm::vec3, m_position, Position)
    SETTER(glm::vec3, m_position, Position)

    GETTER(glm::vec3, m_halfsize, Halfsize)
    SETTER(glm::vec3, m_halfsize, Halfsize)

    GETTER(glm::vec3, m_velocity, Velocity)
    SETTER(glm::vec3, m_velocity, Velocity)

    GETTER(glm::vec3, m_scale, Scale)
    SETTER(glm::vec3, m_scale, Scale)

    GETTER(float, m_linear_damping, LinearDamping)
    SETTER(float, m_linear_damping, LinearDamping)

    GETTER(float, m_friction, Friction)
    SETTER(float, m_friction, Friction)

    GETTER(float, m_vertical_damping, VerticalDamping)
    SETTER(float, m_vertical_damping, VerticalDamping)

    GETTER(bool, m_grounded, Grounded)
    SETTER(bool, m_grounded, Grounded)

    GETTER(float, m_gravity_scale, GravityScale)
    SETTER(float, m_gravity_scale, GravityScale)

    GETTER(bool, m_crouching, Crouching)
    SETTER(bool, m_crouching, Crouching)

private:
    BodyType m_type;
    glm::vec3 m_position;
    glm::vec3 m_halfsize;
    glm::vec3 m_velocity;
    glm::vec3 m_scale {1.0f, 1.0f, 1.0f};
    float m_linear_damping = 0.5;
    float m_friction = 1.0f;
    float m_vertical_damping = 1.0f;
    bool m_grounded = false;
    float m_gravity_scale = 1.0f;
    bool m_crouching = false;
};

#endif  // PHYSICS_HITBOX_H_
