#pragma once
#ifndef INTERFACES_IENTITY_H_
#define INTERFACES_IENTITY_H_

#include <cstdint>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "enginecore/interfaces/IComponent.h"

#include "enginecore/core/physics/Hitbox.h"

class IEntity : IComponent
{
public:
	IEntity() = default;
	virtual ~IEntity() = default;

protected:
	entityid_t m_entt_id;
};

template<typename TYPE>
class EntitySharedPointer
{
public:
	using entity_type = entityid_t;
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


	/// @brief Entity string id (with prefix included)
    std::string const name;

    // /// @brief Physic body type
    // BodyType bodyType = BodyType::DYNAMIC;

    // /// @brief Hitbox size
    // glm::vec3 hitbox {0.25f};

    // /// @brief 'aabb' sensors
    // std::vector<std::pair<size_t, AABB>> boxSensors {};
    // /// @brief 'radius' sensors
    // std::vector<std::pair<size_t, float>> radialSensors {};

    // /// @brief Skeleton ID
    // std::string skeletonName = name;

    /// @brief Does entity prevent blocks setup
    bool blocking = true;

    // /// @brief save-** flags
    // struct 
	// {
    //     bool enabled = true;
    //     struct 
	// 	{
    //         bool textures = false;
    //         bool pose = false;
    //     } skeleton;
    //     struct 
	// 	{
    //         bool velocity = true;
    //         bool settings = true;
    //     } body;
    // } save {};

    // struct 
	// {
    //     entityid_t id;
    //     rigging::SkeletonConfig* skeleton;
    // } rt {};
};


#endif // !INTERFACES_IENTITY_H_
