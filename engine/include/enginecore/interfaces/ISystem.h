#pragma once
#ifndef INTERFACES_ISYSTEM_H_
#define INTERFACES_ISYSTEM_H_

#include "enginecore/utils/types/EntityDefines.h"

enum SystemTypes
{
	OBJECT_CONTROLLING,
	CAMERA_BEHAVIOR,
	PHYSICS,
	AI
};

class ISystem
{
public:
	ISystem() = default;
	virtual ~ISystem() = default;

	virtual void update(EntityRegistry<DefaultEntityIndentifier>& registry) = 0;

private:

};


#endif // !INTERFACES_ISYSTEM_H_