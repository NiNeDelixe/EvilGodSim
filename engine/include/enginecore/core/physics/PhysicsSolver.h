#pragma once
#ifndef PHYSICS_PHYSICSSOLVER_H_
#define PHYSICS_PHYSICSSOLVER_H_

#include "enginecore/core/CoreDefines.h"

#include <vector>
#include <glm/glm.hpp>

#include "enginecore/core/physics/Hitbox.h"

class PhysicsSolver 
{
public:
    PhysicsSolver(glm::vec3 gravity);
    ~PhysicsSolver() = default;

    // void step(const GlobalChunks& chunks, Hitbox& hitbox, float delta,
    //     uint_t substeps, entityid_t entity);

    // void colisionCalc(const GlobalChunks& chunks, Hitbox& hitbox, glm::vec3& vel,
    //     glm::vec3& pos, const glm::vec3 half, float stepHeight);

    // void setSensors(const std::vector<Sensor*>& sensors) { this->m_sensors = std::move(sensors); }

    // void removeSensor(Sensor* sensor);

private:
    glm::vec3 m_gravity;
    std::vector<Sensor*> m_sensors;
};

#endif  // PHYSICS_PHYSICSSOLVER_H_
