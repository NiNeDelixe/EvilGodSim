#pragma once
#ifndef MANAGMENT_ENGINESYSTEMFACTORY_H_
#define MANAGMENT_ENGINESYSTEMFACTORY_H_

#include "enginecore/core/CoreDefines.h"

#include <magic_enum/magic_enum_all.hpp>

#include "enginecore/interfaces/ISystemFactory.h"

#include "enginecore/core/ecs/systems/CameraSystem.h"
#include "enginecore/core/ecs/systems/FreeFlySystem.h"
#include "enginecore/core/ecs/systems/RotationSystem.h"
#include "enginecore/core/ecs/systems/TransformSystem.h"

class EngineSystemFactory : public ISystemFactory
{
public:
    EngineSystemFactory() = default;
    ~EngineSystemFactory() = default;

public:
    virtual std::shared_ptr<ISystem> createSystem(const SystemCategory& category) override;
    virtual SystemsContainer createSystems() override;

private:
    
};

#endif  // MANAGMENT_ENGINESYSTEMFACTORY_H_
