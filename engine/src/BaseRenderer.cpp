#include "enginecore/core/graphics/render/BaseRenderer.h"

void BaseRenderer::vertex(const glm::vec3& coord, const float& u, const float& v, const glm::vec4& light)
{
    m_vertex_buffer[++m_vertex_offset] = coord.x;
    m_vertex_buffer[++m_vertex_offset] = coord.y;
    m_vertex_buffer[++m_vertex_offset] = coord.z;

    m_vertex_buffer[++m_vertex_offset] = u;
    m_vertex_buffer[++m_vertex_offset] = v;
    

    m_vertex_buffer[++m_vertex_offset] = static_cast<uint8_t>(light.r * 255);
    m_vertex_buffer[++m_vertex_offset] = static_cast<uint8_t>(light.g * 255);
    m_vertex_buffer[++m_vertex_offset] = static_cast<uint8_t>(light.b * 255);
    m_vertex_buffer[++m_vertex_offset] = static_cast<uint8_t>(light.a * 255);
}

void BaseRenderer::index(const int& a, const int& b, const int& c, const int& d, const int& e, const int& f)
{
    m_index_buffer[++m_index_size] = m_index_offset + a;
    m_index_buffer[++m_index_size] = m_index_offset + b;
    m_index_buffer[++m_index_size] = m_index_offset + c;
    m_index_buffer[++m_index_size] = m_index_offset + d;
    m_index_buffer[++m_index_size] = m_index_offset + e;
    m_index_buffer[++m_index_size] = m_index_offset + f;
    m_index_offset += 4;
}

void BaseRenderer::vertexAO(const glm::vec3& coord, const float& u, const float& v,
    const glm::vec4& brightness, const glm::vec3& axisX, const glm::vec3& axisY, const glm::vec3& axisZ)
{
    auto pos = coord + axisZ * 0.5f + (axisX + axisY) * 0.5f;
    auto light = pickSoftLight(glm::ivec3(std::round(pos.x), std::round(pos.y), std::round(pos.z)),
        axisX, axisY);
    vertex(coord, u, v, light * brightness);
}

glm::vec4 BaseRenderer::pickSoftLight(const glm::ivec3& coord, const glm::ivec3& right, const glm::ivec3& up) const
{
    return (pickLight(coord) +
        pickLight(coord - right) +
        pickLight(coord - right - up) +
        pickLight(coord - up)) * 0.25f;
}

glm::vec4 BaseRenderer::pickLight(const int& x, const int& y, const int& z) const
{
    return glm::vec4(1.f);
}

glm::vec4 BaseRenderer::pickLight(const glm::ivec3& coord) const
{
    return pickLight(coord.x, coord.y, coord.z);
}
