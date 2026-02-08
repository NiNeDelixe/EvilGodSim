#pragma once
#ifndef SYSTEMS_TRANSFORMSYSTEM_H_
#define SYSTEMS_TRANSFORMSYSTEM_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/interfaces/ISystem.h"

class TransformSystem : public ISystem
{
public:
    TransformSystem() = default;
    ~TransformSystem() = default;

public:
    void update(EntityRegistry<DefaultEntityIndentifier>& registry) override;

private:
    
};

#endif // SYSTEMS_TRANSFORMSYSTEM_H_
