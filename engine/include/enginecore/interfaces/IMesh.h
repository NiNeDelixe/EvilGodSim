#pragma once
#ifndef INTERFACES_IMESH_H_
#define INTERFACES_IMESH_H_

#include "enginecore/core/CoreDefines.h"

#include "enginecore/utils/GLUtils.h"

struct MeshStats
{
public:
    static size_t getDrawCalls()
    {
        size_t result = m_draw_calls;
        m_draw_calls = 0;
        return result;
    }
    static size_t getTrianglesCount()
    {
        size_t result = m_triangles_count;
        m_triangles_count = 0;
        return result;
    }
    static size_t getMeshesCount()
    {
        return m_meshes_count;
    }

    static void incrementDrawCalls()
    {
        ++m_draw_calls;
    }

    static void addTrianglesCount(const size_t& value)
    {
        m_triangles_count += value;
    }

    static void incrementMeshesCount()
    {
        ++m_meshes_count;
    }
    
    static void decrementMeshesCount()
    {
        ++m_meshes_count;
    }

private:
    static size_t m_draw_calls;
    static size_t m_triangles_count;
    static size_t m_meshes_count;
};

struct IndexBufferData 
{
    const uint32_t* indices;
    size_t indices_count;
};

class IMesh
{
protected:
    struct IndexBuffer 
    {
        unsigned int ibo;
        size_t index_count;
    };

public:
    IMesh() { MeshStats::incrementMeshesCount(); }
    virtual ~IMesh() { MeshStats::decrementMeshesCount(); }

public:
    virtual void draw(const GLenum& primitive, const size_t& ibo_index = 0) const = 0;
    virtual void reload(const float* const vertex_buffer, const size_t& vertices,
        const uint32_t* const index_buffer, const size_t& indices) = 0;

protected:
    static constexpr size_t calc_size(const ENGINE_NAMESPACE::UTILS_NAMESPACE::gl::VertexAttribute* const attrs)
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