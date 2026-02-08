#pragma once
#ifndef RENDER_MESH_H_
#define RENDER_MESH_H_

#include <array>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "enginecore/utils/types/CoreTypesDefines.h"
#include "enginecore/utils/GLUtils.h"

#include "enginecore/interfaces/IMesh.h"

struct DefaultAtributes
{
    glm::vec3 position;
    glm::vec2 uv;
    //std::array<float, 4> light;

    /// @brief Base mesh vertex attributes
    /// @brief {3} - cords vertex, {2} - UV atributes, {1} - light compressed value + 3 padding, {0} - end symbol
    static constexpr ENGINE_NAMESPACE::UTILS_NAMESPACE::gl::VertexAttribute ATTRIBUTES[] =
    {
        {ENGINE_NAMESPACE::UTILS_NAMESPACE::gl::VertexAttribute::Type::FLOAT, false, 3},
        {ENGINE_NAMESPACE::UTILS_NAMESPACE::gl::VertexAttribute::Type::FLOAT, false, 2},
        //{UTILS_NAMESPACE::gl::VertexAttribute::Type::FLOAT, false, 4},
        {{}, 0} 
    };
};

template<class VERTEXATRIBUTE = DefaultAtributes>
class Mesh : public IMesh
{
public:
    Mesh(const VERTEXATRIBUTE* vertexBuffer, size_t vertices, std::vector<IndexBufferData> indices = {})
    : m_vao(0), m_vbo(0), m_ibos(), m_vertices_count(0), m_created_old(false)
    {
        static_assert(
            calc_size(VERTEXATRIBUTE::ATTRIBUTES) == sizeof(VERTEXATRIBUTE)
        );
        
        const auto& attrs = VERTEXATRIBUTE::ATTRIBUTES;

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        reload(vertexBuffer, vertices, std::move(indices));

        glBindVertexArray(m_vao);
        // attributes
        int offset = 0;
        for (int i = 0; attrs[i].count; ++i) 
        {
            const auto& attr = attrs[i];
            glVertexAttribPointer(
                i,
                attr.count,
                ENGINE_NAMESPACE::UTILS_NAMESPACE::gl::to_glenum(attr.type),
                attr.normalized,
                sizeof(VERTEXATRIBUTE),
                (GLvoid*)(size_t)offset
            );
            glEnableVertexAttribArray(i);
            offset += attr.size();
        }

        glBindVertexArray(0);
    }

	Mesh(const float* const vertex_buffer, const size_t& vertices, const unsigned int* index_buffer,
		const size_t& indices)
        : m_ibo(0), m_vertices_count(0), m_ibos(), m_indices(0), m_created_old(true)
    {
        static_assert(calc_size(VERTEXATRIBUTE::ATTRIBUTES) == sizeof(VERTEXATRIBUTE),
            "The size of the struct must match the size of the attributes");

        const auto& attributes = VERTEXATRIBUTE::ATTRIBUTES;

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        reload(vertex_buffer, vertices, index_buffer, indices);

        // attributes
        size_t offset = 0;
        for (int i = 0; attributes[i].count; ++i)
        {
            auto atribute_value = attributes[i];
            glVertexAttribPointer(i, atribute_value.count, ENGINE_NAMESPACE::UTILS_NAMESPACE::gl::to_glenum(atribute_value.type),
                atribute_value.normalized, sizeof(VERTEXATRIBUTE),
                reinterpret_cast<GLvoid*>(offset));
            glEnableVertexAttribArray(i);
            offset += atribute_value.size();
        }

        glBindVertexArray(0);
    }

    virtual ~Mesh()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        

        for (int i = m_ibos.size() - 1; i >= 0; --i) 
        {
            glDeleteBuffers(1, &m_ibos[i].ibo);
        }
        if (m_ibo != 0)
            glDeleteBuffers(1, &m_ibo);
    }

public:
    void reload(const float* const vertex_buffer, const size_t& vertices, const uint32_t* const index_buffer, const size_t& indices) override
    {
        m_vertices_count = vertices;
        m_indices = indices;

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        if (vertex_buffer != nullptr && vertices != 0)
        {
            glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(VERTEXATRIBUTE), vertex_buffer, GL_STREAM_DRAW);
        }
        else
        {
            glBufferData(GL_ARRAY_BUFFER, 0, {}, GL_STREAM_DRAW);
        }

        if (index_buffer != nullptr && indices != 0)
        {
            if (m_ibo == 0)
                glGenBuffers(1, &m_ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices, index_buffer, GL_STATIC_DRAW);
        }
        else if (m_ibo != 0)
        {
            glDeleteBuffers(1, &m_ibo);
        }
    }

    void reload(const VERTEXATRIBUTE* vertexBuffer, size_t vertexCount, const std::vector<IndexBufferData>& indices)
    {
        this->m_vertices_count = vertexCount;
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        if (vertexBuffer != nullptr && vertexCount != 0) 
        {
            glBufferData(
                GL_ARRAY_BUFFER,
                vertexCount * sizeof(VERTEXATRIBUTE),
                vertexBuffer,
                GL_STREAM_DRAW
            );
        } else 
        {
            glBufferData(GL_ARRAY_BUFFER, 0, {}, GL_STREAM_DRAW);
        }

        for (size_t i = indices.size(); i < m_ibos.size(); i++) 
        {
            glDeleteBuffers(1, &m_ibos[i].ibo);
        }
        m_ibos.clear();

        for (size_t i = 0; i < indices.size(); i++) 
        {
            const auto& indexBuffer = indices[i];
            m_ibos.emplace_back(0, 0);

            glGenBuffers(1, &m_ibos[i].ibo);
            m_ibos[i].index_count = indexBuffer.indices_count;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibos[i].ibo);
            glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                sizeof(uint32_t) * indexBuffer.indices_count,
                indexBuffer.indices,
                GL_STATIC_DRAW
            );
        }
        glBindVertexArray(0);
    }

    void reload(const VERTEXATRIBUTE* vertexBuffer, size_t vertexCount) 
    {
        static const std::vector<IndexBufferData> indices {};
        reload(vertexBuffer, vertexCount, indices);
    }

    void draw(const GLenum& primitive, const size_t& iboIndex = 0) const override
    {
        MeshStats::incrementDrawCalls();
        size_t triangle_count = 0;

        glBindVertexArray(m_vao);
        if (!m_ibos.empty())
        {
            if (iboIndex < m_ibos.size()) 
            {

                glBindVertexArray(m_vao);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibos[iboIndex].ibo);
                glDrawElements(
                    primitive, m_ibos.at(iboIndex).index_count, GL_UNSIGNED_INT, nullptr
                );
            }
        }
        else if (m_ibo != 0 && m_created_old)
        {
            switch (primitive)
            {
                case GL_TRIANGLES:
                    triangle_count = m_indices / 3;
                    break;
                case GL_TRIANGLE_STRIP:
                case GL_TRIANGLE_FAN:
                    triangle_count = (m_indices >= 3) ? (m_indices - 2) : 0;
                    break;
                case GL_QUADS:
                    triangle_count = (m_indices / 4) * 2;
                    break;
                default:
                    // For non-triangle primitives, count as 0
                    triangle_count = 0;
                    break;
            }

            glDrawElements(primitive, m_indices, GL_UNSIGNED_INT, nullptr);
        }
        else if (m_vertices_count > 0)
        {
            switch (primitive)
            {
                case GL_TRIANGLES:
                    triangle_count = m_vertices_count / 3;
                    break;
                case GL_TRIANGLE_STRIP:
                case GL_TRIANGLE_FAN:
                    triangle_count = (m_vertices_count >= 3) ? (m_vertices_count - 2) : 0;
                    break;
                case GL_QUADS:
                    triangle_count = (m_vertices_count / 4) * 2;
                    break;
                default:
                    // For non-triangle primitives, count as 0
                    triangle_count = 0;
                    break;
            }

            glBindVertexArray(m_vao);
            glDrawArrays(primitive, 0, m_vertices_count);
        }

        glBindVertexArray(0);

        MeshStats::addTrianglesCount(triangle_count);
    }

	void draw() const
    {
        draw(GL_TRIANGLES);
    }

private:
	uint32_t m_vao;
	uint32_t m_vbo;
	uint32_t m_ibo;
	size_t m_indices;
    std::vector<IndexBuffer> m_ibos;
	size_t m_vertices_count;

    bool m_created_old;
};

#endif // !RENDER_MESH_H_