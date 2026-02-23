#pragma once
#ifndef INTERFACES_ISYSTEM_H_
#define INTERFACES_ISYSTEM_H_

#include "enginecore/core/CoreDefines.h"

#include <optional>
#include <unordered_map>

#include "enginecore/utils/types/EntityDefines.h"

#include "enginecore/interfaces/IMetaClass.h"

#include "enginecore/core/ecs/systems/managment/SystemCategory.h"

class ISystem : public IMetaClass
{
public:
	ISystem(const SystemCategory& category) : m_category(category) {}
	ISystem() = default;
	virtual ~ISystem() = default;

	virtual void update(EntityRegistry<DefaultEntityIndentifier>& registry) = 0;

	GETTER(std::optional<SystemCategory>, m_category, Category)

private:
	std::optional<SystemCategory> m_category{};
};

class systems_container
{
public:
    using SystemPtr = std::shared_ptr<ISystem>;

    bool add(const SystemPtr& system)
    {
        auto cat = system->getCategory();

        if (cat.has_value())
        {
            auto [it, inserted] = m_categorized.emplace(*cat, std::move(system));
            return inserted;
        }
        else
        {
            m_uncategorized.emplace_back(std::move(system));
            return true;
        }
    }

    void remove(const SystemCategory& category)
    {
        m_categorized.erase(category);
    }

	void remove(const size_t& i)
    {
        m_uncategorized.erase(m_uncategorized.begin() + i);
    }

    ISystem* get(const SystemCategory& category) const
    {
        auto it = m_categorized.find(category);
        return it != m_categorized.end() ? it->second.get() : nullptr;
    }

	size_t size() const
	{
		return m_categorized.size() + m_uncategorized.size();
	}

public:
	SystemPtr& operator[](const size_t& i)
	{
		return m_uncategorized[i];
	}

	SystemPtr& operator[](const SystemCategory& cat)
	{
		return m_categorized[cat];
	}

	SystemPtr& at(const size_t& i)
	{
		return m_uncategorized.at(i);
	}

	SystemPtr& at(const SystemCategory& cat)
	{
		return m_categorized.at(cat);
	}

public:
	std::unordered_map<SystemCategory, SystemPtr>& getCategorized() { return this->m_categorized; }
	std::vector<SystemPtr>& getUncategorized() { return this->m_uncategorized; }

private:
    std::unordered_map<SystemCategory, SystemPtr> m_categorized;
    std::vector<SystemPtr> m_uncategorized;
};

using SystemsContainer = systems_container;

#endif // !INTERFACES_ISYSTEM_H_