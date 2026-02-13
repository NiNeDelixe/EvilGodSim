#pragma once
#ifndef COMPONENTS_TRANSFORM_H_
#define COMPONENTS_TRANSFORM_H_

#include "enginecore/core/ecs/components/transform/Direction.h"
#include "enginecore/core/ecs/components/transform/Position.h"
#include "enginecore/core/ecs/components/transform/Rotation.h"
#include "enginecore/core/ecs/components/transform/Size.h"

class Transform : public virtual Direction, public virtual Position, public virtual Rotation, public virtual Size
{

};


#endif // !COMPONENTS_TRANSFORM_H_