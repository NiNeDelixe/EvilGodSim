#pragma once
#ifndef SYSTEMS_SYSTEMSMANAGER_H_
#define SYSTEMS_SYSTEMSMANAGER_H_

#include "enginecore/core/CoreDefines.h"

#include <atomic>
#include <unordered_map>

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
        : m_arena(max_concurrency) 
        {}
    ~SystemsManager() {}

public:
    void scheduledSystem(EntityRegistry<DefaultEntityIndentifier>& registry)
    {
        m_arena.execute([this, &registry]() 
        {
            if (!m_systems.getUncategorized().empty())
            {
                ENGTHRDPL::parallel_for(
                    ENGTHRDPL::blocked_range<size_t>(0, m_systems.getUncategorized().size()),
                    [&](const ENGTHRDPL::blocked_range<size_t>& range) 
                    {
                        for (size_t i = range.begin(); i < range.end(); ++i)
                        {
                            auto& system = m_systems[i];

                            m_active_tasks.fetch_add(1, std::memory_order_relaxed);
                            system->update(registry);
                            m_active_tasks.fetch_sub(1, std::memory_order_relaxed);
                        }
                    }
                );
            }
            
            if (!m_systems.getCategorized().empty())
            {
                ENGTHRDPL::parallel_for_each(
                    m_systems.getCategorized().begin(), m_systems.getCategorized().end(),
                    [&](const auto& pair) 
                    {
                        auto& system = pair.second;

                        m_active_tasks.fetch_add(1, std::memory_order_relaxed);
                        system->update(registry);
                        m_active_tasks.fetch_sub(1, std::memory_order_relaxed);
                    }
                );
            }
            
        });
    }

    // void addSystem(const SystemCategory& type, const std::shared_ptr<ISystem>& system) 
    // { 
    //     auto it = m_categories.find(type);
        
    //     if (it != m_categories.end()) 
    //     {
    //         size_t index = std::distance(m_categories.begin(), it);
    //         m_systems[index] = system;
    //     }
    //     else
    //     {
    //         m_systems.push_back(system);
    //         m_categories.insert(type); 
    //     }
    // }

    // void addSystem(const std::shared_ptr<ISystem>& system) 
    // { 
    //     m_systems.push_back(system);
    // }

    template<CONCEPTS_NAMESPACE::IsDerivedFromISystemFactory SYSTEMFACTORY, class... ARGS>
    void emplaceSystems(ARGS&&... args) 
    {
        m_systems = SYSTEMFACTORY(std::forward<decltype(args)>(args)...).createSystems();
    }

public:
    GETTER_VAL(size_t, m_active_tasks, ActiveTasks)

    SETTER(SystemsContainer, m_systems, Systems)

private:
    SystemsContainer m_systems;
    //std::set<SystemCategory> m_categories;
    tbb::task_arena m_arena;
    std::atomic<size_t> m_active_tasks{0};
};

#endif // !SYSTEMS_SYSTEMSMANAGER_H_