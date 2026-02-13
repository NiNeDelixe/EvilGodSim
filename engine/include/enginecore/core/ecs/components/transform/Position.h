#pragma once
#ifndef COMPONENTS_POSITION_H_
#define COMPONENTS_POSITION_H_

#include "enginecore/core/CoreDefines.h"

#include <glm/glm.hpp>

#include "enginecore/interfaces/IComponent.h"

class Position : public IComponent
{
public:
    union
    {
        struct
        {
            fixedpoint_t m_x;
            fixedpoint_t m_y;
            fixedpoint_t m_z;
        };
        glm::fixvec3 m_pos = glm::fixvec3(0);
    };
    
};


#endif // !COMPONENTS_POSITION_H_