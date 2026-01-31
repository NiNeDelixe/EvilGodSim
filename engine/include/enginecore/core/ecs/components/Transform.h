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

        if (m_front_modified)
        {
            m_front_modified = false;
            glm::vec3 front = glm::normalize(m_front);
            glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 right = glm::normalize(glm::cross(front, world_up));
            glm::vec3 up = glm::normalize(glm::cross(right, front));
            
            m_rotation = glm::mat4(
                glm::vec4(right, 0.0f),
                glm::vec4(up, 0.0f),
                glm::vec4(-front, 0.0f), // OpenGL front = -z
                glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
            );
        }
        else
        {
            m_front = glm::vec3(m_rotation * glm::vec4(0, 0, -1, 1));
            m_right = glm::vec3(m_rotation * glm::vec4(1, 0, 0, 1));
            m_up = glm::vec3(m_rotation * glm::vec4(0, 1, 0, 1));
            m_direction = glm::vec3(m_rotation * glm::vec4(0, 0, -1, 1));
            m_direction.y = 0;
            float len = glm::length(m_direction);
            if (len > 0.0f) 
            {
                m_direction.x /= len;
                m_direction.z /= len;
            }
        }

        updateEulerAnglesFromMatrix();
    }
};


#endif // !COMPONENTS_TRANSFORM_H_