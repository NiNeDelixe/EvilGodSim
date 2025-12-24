#pragma once
#ifndef TYPE_GAMEOBJECTSALLOCATOR_H_
#define TYPE_GAMEOBJECTSALLOCATOR_H_

#include "enginecore/core/CoreDefines.h"

#include <memory>

namespace UTILS_NAMESPACE
{
    namespace memory
    {

        template<typename T>
        using GameObjectAllocator = std::allocator<T>;

    };
};

#endif // !TYPE_GAMEOBJECTSALLOCATOR_H_