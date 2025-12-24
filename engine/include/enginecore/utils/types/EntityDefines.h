#pragma once
#ifndef TYPES_ENTITYDEFINES_H_
#define TYPES_ENTITYDEFINES_H_

#include <entt/entt.hpp>

template<class IDENTIFIER>
using EntityRegistry = entt::basic_registry<IDENTIFIER>;
using DefaultEntityIndentifier = entt::entity;
#define ENGINE_ENTITY_NAMESPACE entt

#endif // !TYPES_ENTITYDEFINES_H_