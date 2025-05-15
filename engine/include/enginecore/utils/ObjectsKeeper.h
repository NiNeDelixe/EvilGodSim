#pragma once
#ifndef UTILS_OBJECTSKEEPER_H_

#include <memory>
#include <list>

#include "enginecore/core/CoreDefines.h"

namespace UTILS_NAMESPACE
{
    namespace memory
    {
        /// @brief Keeps shared pointers alive until destruction
        class ObjectsKeeper
        {
        private:
            DISABLE_COPY(ObjectsKeeper);

        public:
            ObjectsKeeper() = default;
            virtual ~ObjectsKeeper() = default;

            ObjectsKeeper(ObjectsKeeper&& keeper) noexcept
                : ptrs(std::move(keeper.ptrs)) {}

        public:
            ObjectsKeeper& operator=(ObjectsKeeper&& keeper) noexcept = default;

        public:
            virtual void keepAlive(std::shared_ptr<void> ptr)
            {
                ptrs.push_back(std::move(ptr));
            }

            virtual void clearKeepedObjects()
            {
                ptrs.clear();
            }

        private:
            std::list<std::shared_ptr<void>> ptrs;
        };
    }
}

#endif // !UTILS_OBJECTSKEEPER_H_