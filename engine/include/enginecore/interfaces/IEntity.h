#pragma once
#ifndef INTERFACES_IENTITY_H_
#define INTERFACES_IENTITY_H_

#include <cstdint>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "enginecore/interfaces/IComponent.h"

class IEntity : IComponent
{
public:
	IEntity() = default;
	virtual ~IEntity() = default;
};

template<typename TYPE>
class EntitySharedPointer
{
public:
	using entity_type = std::uint32_t;
	static constexpr auto null = entt::null;

public:
	//DONT TOUCH!
	constexpr EntitySharedPointer(const entity_type& value = null) noexcept
		: entt(value) {}

public:
	EntitySharedPointer() = default;
	~EntitySharedPointer() = default;

public:
	constexpr operator entity_type() const noexcept { return entt; }

private:
	entity_type entt;
	std::shared_ptr<TYPE> m_pointer = std::make_shared<TYPE>();
};


#endif // !INTERFACES_IENTITY_H_
