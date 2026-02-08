#pragma once
#ifndef SYSTEMS_SYSTEMSMANAGER_H_
#define SYSTEMS_SYSTEMSMANAGER_H_

#include <atomic>
#include <unordered_map>

#include "enginecore/core/LibrariesDefines.h"

#include "enginecore/interfaces/ISystem.h"

enum class SystemCategory 
{
    OBJECT_CONTROLLING,
	CAMERA_BEHAVIOR,
    LOGIC,
    RENDER,
    PHYSICS,
    IO,
    AI
};

class SystemsManager
{
public:
    SystemsManager(int max_concurrency = std::thread::hardware_concurrency()) 
        : m_arena(max_concurrency) {}
    ~SystemsManager() {}

public:
    void scheduledSystem(EntityRegistry<DefaultEntityIndentifier>& registry)
    {
        m_arena.execute([this, &registry]() 
        {
            tbb::parallel_for(
                tbb::blocked_range<size_t>(0, m_systems.size()),
                [&](const tbb::blocked_range<size_t>& range) 
                {
                    for (auto&& system : m_systems) 
                    {
                        m_active_tasks.fetch_add(1, std::memory_order_relaxed);
                        if (auto sys_loc = system.second.lock())
                        {
                            sys_loc->update(registry);
                        }

                        //system.second->update(registry);
                        
                        m_active_tasks.fetch_sub(1, std::memory_order_relaxed);
                    }
                }
            );
        });
    }

    void addSystem(const SystemCategory& type, const std::shared_ptr<ISystem>& system) 
    { 
        auto it = m_systems.find(type);
        if (it != m_systems.end()) 
            it->second = system;
        else
            m_systems.insert({type, system}); 
    }

private:
    std::unordered_map<SystemCategory, std::weak_ptr<ISystem>> m_systems;
    tbb::task_arena m_arena;
    std::atomic<int> m_active_tasks{0};
};

#endif // !SYSTEMS_SYSTEMSMANAGER_H_