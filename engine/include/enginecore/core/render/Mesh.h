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
    //float light;

    /// @brief Base mesh vertex attributes
    /// {3} - cords vertex, {2} - UV atributes, {1} - light compressed value, {0} - end symbol
    static constexpr UTILS_NAMESPACE::gl::VertexAttribute ATTRIBUTES[] =
    {
        {UTILS_NAMESPACE::gl::VertexAttribute::Type::FLOAT, false, 3},
        {UTILS_NAMESPACE::gl::VertexAttribute::Type::FLOAT, false, 2},
        //{VertexAttribute::Type::FLOAT, false, 1},
        //{VertexAttribute::Type::PADDING, false, 3},
        {{}, 0} 
    };
};

template<class VERTEXATRIBUTE = DefaultAtributes>
class Mesh : public IMesh
{
public:
	Mesh(const float* const vertex_buffer, const size_t& vertices, const unsigned int* index_buffer,
		const size_t& indices)
        : m_ibo(0), m_vertices(0), m_indices(0)
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
            glVertexAttribPointer(i, atribute_value.count, UTILS_NAMESPACE::gl::to_glenum(atribute_value.type),
                atribute_value.normalized, sizeof(VERTEXATRIBUTE),
                reinterpret_cast<GLvoid*>(offset));
            glEnableVertexAttribArray(i);
            offset += atribute_value.size();
        }

        glBindVertexArray(0);
    }

    ~Mesh()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        if (m_ibo != 0)
            glDeleteBuffers(1, &m_ibo);
    }

public:
    void reload(const float* const vertex_buffer, const size_t& vertices, const size_t* const index_buffer, const size_t& indices) override
    {
        m_vertices = vertices;
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

    void draw(const GLenum& primitive) const override
    {
        ++MeshStats::m_draw_calls;
        glBindVertexArray(m_vao);
        if (m_ibo != 0)
        {
            glDrawElements(primitive, m_indices, GL_UNSIGNED_INT, nullptr);
        }
        else
        {
            glDrawArrays(primitive, 0, m_vertices);
        }
        glBindVertexArray(0);
    }

	void draw() const
    {
        draw(GL_TRIANGLES);
    }

private:
	uint32_t m_vao;
	uint32_t m_vbo;
	uint32_t m_ibo;
	size_t m_vertices;
	size_t m_indices;
};

#endif // !RENDER_MESH_H_