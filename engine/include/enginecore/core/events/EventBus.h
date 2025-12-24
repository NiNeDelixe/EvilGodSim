#pragma once
#ifndef WINDOW_EVENTBUS_H_
#define WINDOW_EVENTBUS_H_

#include <unordered_map>
#include <map>
#include <vector>
#include <functional>
#include <concepts> 

#include "enginecore/core/CoreDefines.h"
#include "enginecore/utils/types/Delegates.h"

#include "enginecore/interfaces/IEvent.h"

namespace EVENT_NAMESPACE
{
    namespace CONCEPTS_NAMESPACE
    {
        template<typename T>
        concept IsDerivedFromEvent = std::derived_from<T, IEvent>;
    }

    class EventBus 
    {
    public:
        template<CONCEPTS_NAMESPACE::IsDerivedFromEvent T, typename Handler>
        void addListener(Handler&& handler)
        {
            size_t typeId = typeid(T).hash_code();
            m_subscribers[typeId].emplace_back(
                [handler](const IEvent& event) 
                {
                    handler(static_cast<const T&>(event));
                }
            );
        }

        template<CONCEPTS_NAMESPACE::IsDerivedFromEvent T>
        void invoke(const T& event)
        {
            size_t typeId = typeid(T).hash_code();
            auto it = m_subscribers.find(typeId);
            if (it != m_subscribers.end())
            {
                for (auto& subscriber : it->second) 
                {
                    subscriber(event);
                }
            }
        }

    private:
        std::unordered_map<size_t, std::vector<delegates::consumer<const IEvent&>>> m_subscribers;
    };
}

#endif // !WINDOW_EVENTBUS_H_
