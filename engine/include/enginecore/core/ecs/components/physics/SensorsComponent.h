#pragma once
#ifndef PHYSICS_SENSORSCOMPONENT_H_
#define PHYSICS_SENSORSCOMPONENT_H_

#include "enginecore/core/CoreDefines.h"

#include <vector>

#include "enginecore/interfaces/IComponent.h"

#include "enginecore/core/physics/Hitbox.h"

class SensorsComponent : public IComponent
{
public:
    std::vector<Sensor*> sensors;
};

#endif  // PHYSICS_SENSORSCOMPONENT_H_
