#pragma once
#ifndef COMPONENTS_TRANSFORM_H_
#define COMPONENTS_TRANSFORM_H_

#include "enginecore/core/ecs/components/Direction.h"
#include "enginecore/core/ecs/components/Position.h"
#include "enginecore/core/ecs/components/Rotation.h"
#include "enginecore/core/ecs/components/Size.h"

class Transform : public virtual Direction, public virtual Position, public virtual Rotation, public virtual Size
{

public:
    void normalizeVectors() 
    {
        if (glm::length(m_front) < 0.001f) 
            m_front = glm::vec3(0, 0, 1);
        if (glm::length(m_up) < 0.001f) 
            m_up = glm::vec3(0, 1, 0);
        m_front = glm::normalize(m_front);
        m_up = glm::normalize(m_up);

        updateEulerAnglesFromMatrix();
    }
};


#endif // !COMPONENTS_TRANSFORM_H_