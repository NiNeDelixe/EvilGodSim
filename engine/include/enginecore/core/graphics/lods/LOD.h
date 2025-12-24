#pragma once
#ifndef LODS_LOD_H_
#define LODS_LOD_H_

#include <memory>
#include <array>

#include "enginecore/core/graphics/render/Mesh.h"

struct LODAtributes
{
    glm::vec3 position;
    std::array<float, 4> light;

    /// @brief Base mesh vertex attributes
    /// @brief {3} - cords vertex, {1} - light compressed value + 3 padding, {0} - end symbol
    static constexpr UTILS_NAMESPACE::gl::VertexAttribute ATTRIBUTES[] =
    {
        {UTILS_NAMESPACE::gl::VertexAttribute::Type::FLOAT, false, 3},
        {UTILS_NAMESPACE::gl::VertexAttribute::Type::FLOAT, false, 4},
        {{}, 0}
    };
};

class LOD : public Mesh<LODAtributes>
{
public:
	LOD(const size_t& lod_factor, 
        const float* const vertex_buffer, const size_t& vertices,
        const unsigned int* index_buffer, const size_t& indices)
		: Mesh<LODAtributes>(vertex_buffer, vertices, index_buffer, indices),
        m_lod_factor(lod_factor) {}
	~LOD() = default;

public:
    //static LOD simplifyLOD(LOD& lod);

private:
	size_t m_lod_factor;
};


#endif // !LODS_LOD_H_