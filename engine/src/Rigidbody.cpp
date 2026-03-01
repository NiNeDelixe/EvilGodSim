#include "enginecore/core/physics/Rigidbody.h"

Rigidbody::Rigidbody(const entt::entity &entity)
    : m_hitbox(BodyType::STATIC, {}, {})
{    
    SensorParams params {};
    params.aabb = AABB({1, 1, 1});
    m_sensors.push_back(Sensor 
    {
        true,
        SensorType::AABB,
        0,
        entt::entt_traits<entt::entity>::to_entity(entity),
        params,
        params,
        {},
        {},
        [](entityid_t, size_t){ LOG(WARNING) << "no enter callback"; },
        [](entityid_t, size_t){ LOG(WARNING) << "no exit callback"; }
    });

    // m_sensors.resize(def.radialSensors.size() + def.boxSensors.size());
    // for (auto& [i, box] : def.boxSensors) 
    // {
        
    // }
    // for (auto& [i, radius] : def.radialSensors) 
    // {
    //     SensorParams params {};
    //     params.radial = glm::vec4(radius);
    //     m_sensors[i] = Sensor 
    //     {
    //         true,
    //         SensorType::RADIUS,
    //         i,
    //         id,
    //         params,
    //         params,
    //         {},
    //         {}//,
    //         // create_sensor_callback<scripting::on_sensor_enter>(entities),
    //         // create_sensor_callback<scripting::on_sensor_exit>(entities)
    //     };
    // }
}