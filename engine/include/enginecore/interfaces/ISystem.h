#pragma once
#ifndef INTERFACES_ISYSTEM_H_
#define INTERFACES_ISYSTEM_H_

#include <entt/entt.hpp>

class ISystem
{
public:
	ISystem() = default;
	virtual ~ISystem() = default;

	virtual void update(entt::registry& registry) = 0;

private:

};


#endif // !INTERFACES_ISYSTEM_H_