#pragma once
#ifndef SYSTEMS_ROTATIONSYSTEM_H_
#define SYSTEMS_ROTATIONSYSTEM_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/interfaces/ISystem.h"

#include "enginecore/core/ecs/components/transform/Rotation.h"
#include "enginecore/core/ecs/components/transform/Transform.h"

class RotationSystem : public ISystem
{
public:
    RotationSystem();
    ~RotationSystem() = default;

public:
    void update(EntityRegistry<DefaultEntityIndentifier>& registry) override;

private:
    
};

#endif  // SYSTEMS_ROTATIONSYSTEM_H_
