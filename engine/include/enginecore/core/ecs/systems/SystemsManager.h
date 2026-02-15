#pragma once
#ifndef SYSTEMS_SYSTEMSMANAGER_H_
#define SYSTEMS_SYSTEMSMANAGER_H_

#include "enginecore/core/CoreDefines.h"

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
    AI,
    TRANSFORM,
    ROTATION
};

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
            tbb::parallel_for(
                tbb::blocked_range<size_t>(0, m_systems.size()),
                [&](const tbb::blocked_range<size_t>& range) 
                {
                    for (size_t i = range.begin(); i < range.end(); ++i)
                    {
                        auto& system = m_systems[i];
                        if (auto sys_loc = system.lock())
                        {
                            m_active_tasks.fetch_add(1, std::memory_order_relaxed);
                            sys_loc->update(registry);
                            m_active_tasks.fetch_sub(1, std::memory_order_relaxed);
                        }
                        else
                        {
                            auto it = m_categories.begin();
                            std::advance(it, index);
                            LOG(WARNING) << "ECS System pointer expired: " << magic_enum::enum_name(*it);
                        }
                    }
                }
            );
        });
    }

    void addSystem(const SystemCategory& type, const std::shared_ptr<ISystem>& system) 
    { 
        auto it = m_categories.find(type);
        
        if (it != m_categories.end()) 
        {
            size_t index = std::distance(m_categories.begin(), it);
            m_systems[index] = system;
        }
        else
        {
            m_systems.push_back(system);
            m_categories.insert(type); 
        }
    }

public:
    GETTER_VAL(size_t, m_active_tasks, ActiveTasks)

private:
    std::vector<std::weak_ptr<ISystem>> m_systems;
    std::set<SystemCategory> m_categories;
    tbb::task_arena m_arena;
    std::atomic<size_t> m_active_tasks{0};
};

#endif // !SYSTEMS_SYSTEMSMANAGER_H_