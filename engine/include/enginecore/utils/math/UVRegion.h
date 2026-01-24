#pragma once
#ifndef MATH_UVREGION_H_
#define MATH_UVREGION_H_

#include <cmath>

#include <glm/vec2.hpp>

struct UVRegion 
{
public:
    UVRegion(float m_u1, float v1, float u2, float v2)
        : m_u1(m_u1), m_v1(v1), m_u2(u2), m_v2(v2) { }

    UVRegion() : m_u1(0.0f), m_v1(0.0f), m_u2(1.0f), m_v2(1.0f) { }

    inline float getWidth() const 
    {
        return fabs(m_u2 - m_u1);
    }

    inline float getHeight() const 
    {
        return fabs(m_v2 - m_v1);
    }

    void autoSub(float w, float h, float x, float y) 
    {
        x *= 1.0f - w;
        y *= 1.0f - h;
        float uvw = getWidth();
        float uvh = getHeight();
        m_u1 = m_u1 + uvw * x;
        m_v1 = m_v1 + uvh * y;
        m_u2 = m_u1 + uvw * w;
        m_v2 = m_v1 + uvh * h;
    }

    inline glm::vec2 apply(const glm::vec2& uv) 
    {
        float w = getWidth();
        float h = getHeight();
        return glm::vec2(m_u1 + uv.x * w, m_v1 + uv.y * h);
    }

    void scale(float x, float y) 
    {
        float w = getWidth();
        float h = getHeight();
        float cx = (m_u1 + m_u2) * 0.5f;
        float cy = (m_v1 + m_v2) * 0.5f;
        m_u1 = cx - w * 0.5f * x;
        m_v1 = cy - h * 0.5f * y;
        m_u2 = cx + w * 0.5f * x;
        m_v2 = cy + h * 0.5f * y;
    }

    SSETTER(float, m_u1, u1)
    SSETTER(float, m_v1, v1)
    SSETTER(float, m_u2, u2)
    SSETTER(float, m_v2, v2)

    SGETTER(float, m_u1, u1)
    SGETTER(float, m_v1, v1)
    SGETTER(float, m_u2, u2)
    SGETTER(float, m_v2, v2)

public:
    float m_u1;
    float m_v1;
    float m_u2;
    float m_v2;
};

#endif // !MATH_UVREGION_H_