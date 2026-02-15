#pragma once
#ifndef INTERFACES_ISYSTEMFACTORY_H_
#define INTERFACES_ISYSTEMFACTORY_H_

#include <memory>

#include "enginecore/interfaces/ISystem.h"

class ISystemFactory
{
public:
    ISystemFactory() = default;
    virtual ~ISystemFactory() = default;

    virtual std::vector<std::unique_ptr<ISystem>> createSystems() = 0;
};

#endif // INTERFACES_ISYSTEMFACTORY_H_
