#pragma once
#ifndef RENDER_MODELRENDERER_H_
#define RENDER_MODELRENDERER_H_

#include "enginecore/core/CoreDefines.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#undef GLM_ENABLE_EXPERIMENTAL

#include "enginecore/core/EngineCoreApplication.h"

#include "enginecore/core/graphics/render/BaseRenderer.h"

#include "enginecore/core/ecs/components/ModelComponent.h"
#include "enginecore/core/ecs/components/transform/RenderTransform.h"

class ModelRenderer : public BaseRenderer
{
public:
	ModelRenderer()
		: BaseRenderer(1) 
	{
		
	}

public:
	void render() override;
	std::shared_ptr<IMesh> createMesh() override;

private:

};


#endif // !RENDER_MODELRENDERER_H_