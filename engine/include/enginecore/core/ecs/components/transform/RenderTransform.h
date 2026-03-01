#pragma once
#ifndef COMPONENTS_RENDERTRANSFORM_H_
#define COMPONENTS_RENDERTRANSFORM_H_

#include <enginecore/core/CoreDefines.h>

#include <glm/glm.hpp>

#include <enginecore/interfaces/IComponent.h>

class RenderTransform : public IComponent
{
public:
    glm::vec3 relative_position;
    glm::quat relative_rotation;
};

#endif  // COMPONENTS_RENDERTRANSFORM_H_
