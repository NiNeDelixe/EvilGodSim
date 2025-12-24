#pragma once
#ifndef RENDERER_CUBERENDERER_H_
#define RENDERER_CUBERENDERER_H_

#include <enginecore/core/graphics/render/BaseRenderer.h>
#include <enginecore/core/graphics/render/Mesh.h>

#include <enginecore/utils/math/UVRegion.h>

struct CubeVertex 
{
    glm::vec3 position;
    glm::vec2 uv;
    std::array<uint8_t, 4> color;

    static constexpr ENGNMSP::UTLSNMSP::gl::VertexAttribute ATTRIBUTES[] = {
        {ENGNMSP::UTLSNMSP::gl::VertexAttribute::Type::FLOAT, false, 3},
        {ENGNMSP::UTLSNMSP::gl::VertexAttribute::Type::FLOAT, false, 2},
        {ENGNMSP::UTLSNMSP::gl::VertexAttribute::Type::UNSIGNED_BYTE, true, 4},
        {{}, 0} };
};

class CubeRenderer : public BaseRenderer
{
public:
	CubeRenderer() = default;
	~CubeRenderer() = default;

public:
	std::shared_ptr<IMesh> createMesh() override;
	void render() override;

    void face(const glm::vec3& coord,
        const float& w, const float& h, const float& d,
        const glm::vec3& axisX,
        const glm::vec3& axisY,
        const glm::vec3& axisZ,
        const UVRegion& region,
        const glm::vec4(&lights)[4],
        const glm::vec4& tint);

private:

};


#endif // !RENDERER_CUBERENDERER_H_