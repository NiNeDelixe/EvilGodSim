#pragma once
#ifndef PHYSICS_RIGIDBODYCOMPONENT_H_
#define PHYSICS_RIGIDBODYCOMPONENT_H_

#include <enginecore/core/CoreDefines.h>

#include <enginecore/interfaces/IComponent.h>

#include <enginecore/core/physics/Rigidbody.h>

class RigidBodyComponent : public IComponent
{
public:
    Rigidbody rigidbody;
};


#endif  // PHYSICS_RIGIDBODYCOMPONENT_H_
