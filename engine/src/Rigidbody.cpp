#include "enginecore/core/physics/Rigidbody.h"

Rigidbody::Rigidbody(const entt::entity &entity)
    : m_hitbox(BodyType::STATIC, {}, {})
{
    // m_sensors.resize(def.radialSensors.size() + def.boxSensors.size());
    // for (auto& [i, box] : def.boxSensors) {
    //     SensorParams params {};
    //     params.aabb = box;
    //     m_sensors[i] = Sensor {
    //         true,
    //         SensorType::AABB,
    //         i,
    //         id,
    //         params,
    //         params,
    //         {},
    //         {},
    //         create_sensor_callback<scripting::on_sensor_enter>(entities),
    //         create_sensor_callback<scripting::on_sensor_exit>(entities)};
    // }
    // for (auto& [i, radius] : def.radialSensors) {
    //     SensorParams params {};
    //     params.radial = glm::vec4(radius);
    //     m_sensors[i] = Sensor {
    //         true,
    //         SensorType::RADIUS,
    //         i,
    //         id,
    //         params,
    //         params,
    //         {},
    //         {},
    //         create_sensor_callback<scripting::on_sensor_enter>(entities),
    //         create_sensor_callback<scripting::on_sensor_exit>(entities)};
    // }
}