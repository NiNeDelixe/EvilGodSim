#pragma once
#ifndef RENDER_BATCH2D_H_
#define RENDER_BATCH2D_H_

#include "enginecore/core/CoreDefines.h"

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "enginecore/core/assets/texture/GLTexture.h"
#include "enginecore/core/graphics/render/Mesh.h"
#include "enginecore/utils/math/UVRegion.h"
#include "enginecore/utils/GLUtils.h"
#include "enginecore/interfaces/IFlushable.h"

struct Batch2DVertexAtributes 
{
    glm::vec2 position;
    glm::vec2 uv;
    glm::vec4 color;

    static constexpr ENGNMSP::UTLSNMSP::gl::VertexAttribute ATTRIBUTES[] 
    {
        {ENGNMSP::UTLSNMSP::gl::VertexAttribute::Type::FLOAT, false, 2},
        {ENGNMSP::UTLSNMSP::gl::VertexAttribute::Type::FLOAT, false, 2},
        {ENGNMSP::UTLSNMSP::gl::VertexAttribute::Type::FLOAT, false, 4},
        {{}, 0}
    };
};

class Batch2D : public IFlushable 
{
public:
    Batch2D(const size_t& capacity);
    ~Batch2D() = default;

private:
    void setPrimitive(const ENGNMSP::utils::gl::DrawPrimitive& primitive);

    void vertex(float x, float y,
        float u, float v,
        float r, float g, float b, float a);
    
    void vertex(glm::vec2 point,
        glm::vec2 uvpoint,
        float r, float g, float b, float a);

public:
    void begin();
    void texture(const Texture* texture);
    void untexture();
    void sprite(float x, float y, float w, float h, const UVRegion& region, glm::vec4 tint);
    void sprite(float x, float y, float w, float h, int atlasRes, int index, glm::vec4 tint);
    void sprite(float x, float y, float w, float h, float skew, int atlasRes, int index, glm::vec4 tint);
    void point(float x, float y, float r, float g, float b, float a);
    
public:
    void resetColor() 
    {
        this->m_color = glm::vec4(1.0f);
    }
    
    void line(float x1, float y1, 
        float x2, float y2, 
        float r, float g, float b, float a);
        
    void lineRect(float x, float y, float w, float h);

    void rect(float x, float y,
        float w, float h,
        float ox, float oy,
        float angle, UVRegion region,
        bool flippedX, bool flippedY,
        glm::vec4 tint);
        
    void rect(float x, float y, float w, float h);

    void rect(float x, float y, float w, float h,
        float u, float v, float tx, float ty,
        float r, float g, float b, float a);
        
    void rect(float x, float y, float w, float h,
        float r0, float g0, float b0,
        float r1, float g1, float b1,
        float r2, float g2, float b2,
        float r3, float g3, float b3,
        float r4, float g4, float b4, int sh);

    void parallelogram(float x, float y, float w, float h, float skew,
        float u, float v, float tx, float ty,
        float r, float g, float b, float a);
        
    void triangle(const float& x1, const float& y1, const float& x2,
        const float& y2, const float& x3, const float& y3);

    void flush() override;
    
    void lineWidth(const float& width);
    
public:
    SETTER(glm::vec4, m_color, Color)
    GETTER(glm::vec4, m_color, Color)
    
    SETTER(UVRegion, m_region, Region)
    
    void setColor(const int& r, const int& g, const int& b, const int& a = 255) 
    {
        this->m_color = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

private:
    std::shared_ptr<Batch2DVertexAtributes[]> m_buffer;
    size_t m_capacity;
    std::shared_ptr<Mesh<Batch2DVertexAtributes>> m_mesh;
    std::shared_ptr<Texture> m_blank;
    size_t m_index;
    glm::vec4 m_color;
    const Texture* m_currentTexture;
    ENGNMSP::utils::gl::DrawPrimitive m_primitive = ENGNMSP::utils::gl::DrawPrimitive::triangle;
    UVRegion m_region {0.0f, 0.0f, 1.0f, 1.0f};
};

#endif  // RENDER_BATCH2D_H_
