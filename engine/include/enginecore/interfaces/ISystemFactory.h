#pragma once
#ifndef INTERFACES_ISYSTEMFACTORY_H_
#define INTERFACES_ISYSTEMFACTORY_H_

#include <memory>
#include <vector>

#include "enginecore/interfaces/ISystem.h"

#include "enginecore/core/ecs/systems/managment/SystemCategory.h"

class ISystemFactory
{
public:
    ISystemFactory() = default;
    virtual ~ISystemFactory() = default;
    
    virtual SystemsContainer createSystems() = 0;
};

#endif  // INTERFACES_ISYSTEMFACTORY_H_
