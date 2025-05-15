#pragma once
#ifndef COMPONENTS_TRANSFORM_H_
#define COMPONENTS_TRANSFORM_H_

#include "enginecore/core/ecs/components/Direction.h"
#include "enginecore/core/ecs/components/Position.h"
#include "enginecore/core/ecs/components/Rotation.h"

class Transform : public virtual Direction, public virtual Position, public virtual Rotation
{

};


#endif // !COMPONENTS_TRANSFORM_H_