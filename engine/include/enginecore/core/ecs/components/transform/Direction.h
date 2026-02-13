#pragma once
#ifndef COMPONENTS_DIRECTION_H_
#define COMPONENTS_DIRECTION_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "enginecore/interfaces/IComponent.h"

class Direction : public IComponent
{
public:
    glm::vec3 m_front{};
    glm::vec3 m_up{};
    glm::vec3 m_right{};
    glm::vec3 m_direction{};

    bool m_front_modified = false;
};


#endif // !COMPONENTS_DIRECTION_H_