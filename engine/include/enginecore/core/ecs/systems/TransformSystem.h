#pragma once
#ifndef SYSTEMS_TRANSFORMSYSTEM_H_
#define SYSTEMS_TRANSFORMSYSTEM_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/interfaces/ISystem.h"

#include "enginecore/core/ecs/components/transform/Transform.h"

class TransformSystem : public ISystem
{
public:
    TransformSystem();
    ~TransformSystem() = default;

public:
    void update(EntityRegistry<DefaultEntityIndentifier>& registry) override;

private:
    
};

#endif  // SYSTEMS_TRANSFORMSYSTEM_H_
