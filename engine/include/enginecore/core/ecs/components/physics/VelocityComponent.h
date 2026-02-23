#pragma once
#ifndef PHYSICS_VELOCITYCOMPONENT_H_
#define PHYSICS_VELOCITYCOMPONENT_H_

#include <enginecore/core/CoreDefines.h>

#include <enginecore/interfaces/IComponent.h>

class VelocityComponent : public IComponent
{
public:
    glm::vec3 vector;
};

#endif  // PHYSICS_VELOCITYCOMPONENT_H_
