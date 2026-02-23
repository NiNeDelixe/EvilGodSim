#pragma once
#ifndef PHYSICS_GRAVITYCOMPONENT_H_
#define PHYSICS_GRAVITYCOMPONENT_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/interfaces/IComponent.h"

class GravityComponent : public IComponent
{
public:
    float force;
};

#endif  // PHYSICS_GRAVITYCOMPONENT_H_
