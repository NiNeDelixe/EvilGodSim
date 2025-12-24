#pragma once
#ifndef TYPES_GAMEOBJECT_H_
#define TYPES_GAMEOBJECT_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/interfaces/IEntity.h"

namespace CORE_NAMESPACE
{

	class GameObject : public IEntity
	{
	public:
		GameObject() = default;
		~GameObject() = default;

	private:

	};

	
};


#endif // !TYPES_GAMEOBJECT_H_