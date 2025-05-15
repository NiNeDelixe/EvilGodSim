#pragma once
#ifndef INTERFACES_IMESH_H_
#define INTERFACES_IMESH_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/utils/GLUtils.h"

struct MeshStats
{
    static size_t m_draw_calls;
    static size_t m_meshes_count;
};

class IMesh
{
public:
    IMesh() { ++MeshStats::m_meshes_count; }
    virtual ~IMesh() { --MeshStats::m_meshes_count; }

public:
    virtual void draw(const GLenum& primitive) const = 0;
    virtual void reload(const float* const vertex_buffer, const size_t& vertices,
        const size_t* const index_buffer, const size_t& indices) = 0;

protected:
    static constexpr size_t calc_size(const UTILS_NAMESPACE::gl::VertexAttribute* const attrs)
    {
        size_t vertex_size = 0;
        for (size_t i = 0; attrs[i].count; ++i)
        {
            vertex_size += attrs[i].size();
        }
        return vertex_size;
    }

private:

};


#endif // !INTERFACES_IMESH_H_