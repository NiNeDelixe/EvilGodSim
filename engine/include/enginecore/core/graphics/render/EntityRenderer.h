#pragma once
#ifndef RENDER_ENTITYRENDERER_H_
#define RENDER_ENTITYRENDERER_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/core/graphics/render/Mesh.h"

class EntityRenderer
{
public:
	EntityRenderer() = default;
	~EntityRenderer() = default;

public:
	std::shared_ptr<Mesh<>> createMesh()

private:

};

#endif // !RENDER_ENTITYRENDERER_H_