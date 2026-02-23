#pragma once
#ifndef SYSTEMS_SYSTEMSMANAGER_H_
#define SYSTEMS_SYSTEMSMANAGER_H_

#include "enginecore/core/CoreDefines.h"

#include <atomic>
#include <shared_mutex>

#include "enginecore/core/LibrariesDefines.h"

#include "enginecore/interfaces/ISystem.h"
#include "enginecore/interfaces/ISystemFactory.h"

#include "enginecore/core/ecs/systems/managment/SystemCategory.h"

namespace CONCEPTS_NAMESPACE
{
    template<typename T>
    concept IsDerivedFromISystemFactory = std::derived_from<T, ISystemFactory>;
}

class SystemsManager
{
public:
    SystemsManager(int max_concurrency = std::thread::hardware_concurrency()) 
        : m_arena(max_concurrency > 0 ? max_concurrency : 1) 
        {}
    ~SystemsManager() = default;

public:
    void scheduledSystem(EntityRegistry<DefaultEntityIndentifier>& registry)
    {
        m_arena.execute([this, &registry]() 
        {
            if (!m_systems.getUncategorized().empty())
            {
                parallelUpdate(
                    m_systems.getUncategorized().begin(),
                    m_systems.getUncategorized().end(),
                    registry
                );
            }
            
            if (!m_systems.getCategorized().empty())
            {
                parallelUpdate(
                    m_systems.getCategorized().begin(),
                    m_systems.getCategorized().end(),
                    registry
                );
            }
            
        });
    }

    template<typename ITERATOR>
    void parallelUpdate(ITERATOR begin,
                        ITERATOR end,
                        EntityRegistry<DefaultEntityIndentifier>& registry)
    {
        ENGTHRDPL::parallel_for_each(
            begin, end,
            [&](auto& element)
            {
                auto&& system = extractSystem(element);
                m_active_tasks.fetch_add(1, std::memory_order_relaxed);
                system->update(registry);
                m_active_tasks.fetch_sub(1, std::memory_order_relaxed);
            }
        );
    }

    static ISystem* extractSystem(auto& element)
    {
        if constexpr (std::is_same_v<
            std::decay_t<decltype(element)>,
            std::shared_ptr<ISystem>>)
        {
            return element.get();
        }
        else
        {
            return element.second.get();
        }
    }

    template<CONCEPTS_NAMESPACE::IsDerivedFromISystemFactory SYSTEMFACTORY, class... ARGS>
    void emplaceSystems(ARGS&&... args) 
    {
        SYSTEMFACTORY factory(std::forward<ARGS>(args)...);
        m_systems = factory.createSystems();
    }

public:
    GETTER_VAL(size_t, m_active_tasks, ActiveTasks)

    SETTER(SystemsContainer, m_systems, Systems)

private:
    mutable std::shared_mutex m_systems_mutex;

    SystemsContainer m_systems;
    tbb::task_arena m_arena;
    std::atomic<size_t> m_active_tasks{0};
};

#endif // !SYSTEMS_SYSTEMSMANAGER_H_