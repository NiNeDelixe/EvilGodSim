#include "CubeRenderer.h"

std::shared_ptr<IMesh> CubeRenderer::createMesh()
{
    UVRegion texfaces[6] = { UVRegion(), UVRegion(), UVRegion(), UVRegion(), UVRegion(), UVRegion() };
    glm::vec3 icoord = {};
    bool lights = true;
    glm::vec3 size = glm::vec3();
    glm::vec3 X(1, 0, 0);
    glm::vec3 Y(0, 1, 0);
    glm::vec3 Z(0, 0, 1);
    glm::vec3 coord(icoord);
    auto tint = pickLight(icoord);
    //face(coord, X * size.x, Y * size.y, Z * size.z, texfaces[5], tint, lights); // north
    //face(coord, -X * size.x, Y * size.y, -Z * size.z, texfaces[4], tint, lights); // south

    //face(coord, X * size.x, -Z * size.z, Y * size.y, texfaces[3], tint, lights); // top
    //face(coord, -X * size.x, -Z * size.z, -Y * size.y, texfaces[2], tint, lights); // bottom

    //face(coord, -Z * size.z, Y * size.y, X * size.x, texfaces[1], tint, lights); // west
    //face(coord, Z * size.z, Y * size.y, -X * size.x, texfaces[0], tint, lights); // east
	//return std::make_shared<Mesh<CubeVertex>>(m_vertex_buffer.get(), m_vertex_offset, m_index_buffer.get(), m_index_offset);
    return {};
}

void CubeRenderer::render()
{
	m_meshes.insert(createMesh());
}

void CubeRenderer::face(const glm::vec3& coord, 
	const float& w, const float& h, const float& d,
	const glm::vec3& axisX, const glm::vec3& axisY, const glm::vec3& axisZ,
	const UVRegion& region, const glm::vec4(&lights)[4], const glm::vec4& tint)
{
    if (m_vertex_offset + 4 >= m_capacity)
    {
        m_overflow = true;
        return;
    }
    auto X = axisX * w;
    auto Y = axisY * h;
    auto Z = axisZ * d;
    float s = 0.5f;
    vertex(coord + (-X - Y + Z) * s, region.m_u1, region.m_v1, lights[0] * tint);
    vertex(coord + (X - Y + Z) * s, region.m_u2, region.m_v1, lights[1] * tint);
    vertex(coord + (X + Y + Z) * s, region.m_u2, region.m_v2, lights[2] * tint);
    vertex(coord + (-X + Y + Z) * s, region.m_u1, region.m_v2, lights[3] * tint);
    index(0, 1, 3, 1, 2, 3);
}
