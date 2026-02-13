#pragma once
#ifndef MATH_AABB_H_
#define MATH_AABB_H_

#include <glm/glm.hpp>

/// @brief Axis Aligned Bounding Box
struct AABB 
{
public:
    AABB() = default;

    AABB(glm::vec3 size) 
        : m_a(0.0f), m_b(size) {}

    AABB(glm::vec3 a, glm::vec3 b) 
        : m_a(a), m_b(b) {}

    /// @brief Get AABB point with minimal x,y,z
    inline glm::vec3 min() const 
    {
        return glm::min(m_a, m_b);
    }

    /// @brief Get AABB point with minimal x,y,z
    inline glm::vec3 max() const 
    {
        return glm::max(m_a, m_b);
    }

    /// @brief Get AABB dimensions: width, height, depth
    inline glm::vec3 size() const 
    {
        return glm::vec3(fabs(m_b.x - m_a.x), fabs(m_b.y - m_a.y), fabs(m_b.z - m_a.z));
    }

    inline glm::vec3 center() const 
    {
        return (m_a + m_b) * 0.5f;
    }

    inline AABB translated(const glm::vec3& pos) const 
    {
        return AABB(m_a + pos, m_b + pos);
    }

    /// @brief Multiply AABB size from center
    inline void scale(const glm::vec3 mul) 
    {
        glm::vec3 center = (m_a + m_b) * 0.5f;
        m_a = (m_a - center) * mul + center;
        m_b = (m_b - center) * mul + center;
    }

    /// @brief Multiply AABB size from given origin
    inline void scale(const glm::vec3 mul, const glm::vec3 orig) 
    {
        glm::vec3 beg = min();
        glm::vec3 end = max();
        glm::vec3 center = glm::mix(beg, end, orig);
        m_a = (m_a - center) * mul + center;
        m_b = (m_b - center) * mul + center;
    }

    /// @brief Check if given point is inside
    inline bool contains(const glm::vec3 pos) const 
    {
        const glm::vec3 p = min();
        const glm::vec3 s = size();
        return !(
            pos.x < p.x || pos.y < p.y || pos.z < p.z || pos.x >= p.x + s.x ||
            pos.y >= p.y + s.y || pos.z >= p.z + s.z
        );
    }

    void fix() 
    {
        auto beg = min();
        auto end = max();
        m_a = beg;
        m_b = end;
    }

    inline void addPoint(glm::vec3 p) 
    {
        m_a = glm::min(m_a, p);
        m_b = glm::max(m_b, p);
    }

    /// TODO: optimize
    void transform(const glm::mat4& matrix) 
    {
        auto pa = m_a;
        auto pb = m_b;
        m_a = matrix * glm::vec4(m_a, 1.0f);
        m_b = matrix * glm::vec4(m_b, 1.0f);
        fix();
        addPoint(matrix * glm::vec4(pb.x, pa.y, pa.z, 1.0f));
        addPoint(matrix * glm::vec4(pb.x, pb.y, pa.z, 1.0f));
        addPoint(matrix * glm::vec4(pb.x, pb.y, pb.z, 1.0f));
        addPoint(matrix * glm::vec4(pa.x, pb.y, pa.z, 1.0f));
        addPoint(matrix * glm::vec4(pa.x, pa.y, pb.z, 1.0f));
        addPoint(matrix * glm::vec4(pb.x, pa.y, pb.z, 1.0f));
    }

    inline bool intersect(const AABB& aabb) {
        return (
            m_a.x <= aabb.m_b.x && m_b.x >= aabb.m_a.x && m_a.y <= aabb.m_b.y &&
            m_b.y >= aabb.m_a.y && m_a.z <= aabb.m_b.z && m_b.z >= aabb.m_a.z
        );
    }

    inline bool intersect(const AABB& aabb, float margin) {
        return (
            m_a.x <= aabb.m_b.x + margin && m_b.x >= aabb.m_a.x - margin &&
            m_a.y <= aabb.m_b.y + margin && m_b.y >= aabb.m_a.y - margin &&
            m_a.z <= aabb.m_b.z + margin && m_b.z >= aabb.m_a.z - margin
        );
    }

public:
    SGETTER(glm::vec3, m_a, a)
    SSETTER(glm::vec3, m_a, a)

    SGETTER(glm::vec3, m_b, b)
    SSETTER(glm::vec3, m_b, b)

private:
    glm::vec3 m_a {0.0f};
    glm::vec3 m_b {1.0f, 1.0f, 1.0f};
};

#endif  // MATH_AABB_H_
