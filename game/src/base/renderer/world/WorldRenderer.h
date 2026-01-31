#pragma once
#ifndef RENDER_WORLDRENDERER_H_
#define RENDER_WORLDRENDERER_H_

#include <unordered_map>

#include <enginecore/core/EngineCoreApplication.h>

#include <enginecore/core/graphics/render/ModelRenderer.h>

#include <enginecore/core/ecs/components/PlayerComponent.h>

#include "base/world/Level.h"

class WorldRenderer 
{
public:
    WorldRenderer(const std::weak_ptr<Level>& world);
    ~WorldRenderer() = default;

public:
    void render();

private:
    void prepareShaders();

private:
    std::weak_ptr<Level> m_world;

    std::shared_ptr<ModelRenderer> m_model_renderer;
};

#endif // !RENDER_WORLDRENDERER_H_