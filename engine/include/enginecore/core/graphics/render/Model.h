#pragma once
#ifndef RENDER_MODEL_H_
#define RENDER_MODEL_H_

#include "enginecore/core/CoreDefines.h"

#include <vector>
#include <memory>

#include "enginecore/interfaces/IAsset.h"
#include "enginecore/core/graphics/render/Mesh.h"

class Model : public IAsset
{
public:
    Model() = default;
    virtual ~Model() = default;

    void addMesh(std::shared_ptr<Mesh<DefaultAtributes>> mesh)
    {
        m_meshes.push_back(std::move(mesh));
        this->m_is_loaded = !m_meshes.empty();
    }

public:
    void draw() const
    {
        for (const auto& mesh : m_meshes)
        {
            mesh->draw();
        }
    }

public:
    GETTER(std::vector<std::shared_ptr<Mesh<DefaultAtributes>>>, m_meshes, Meshes);

private:
    std::vector<std::shared_ptr<Mesh<DefaultAtributes>>> m_meshes;
};

#endif // !RENDER_MODEL_H_