#pragma once
#ifndef RENDER_DRAWCONTEXT_H_
#define RENDER_DRAWCONTEXT_H_

#include "enginecore/core/CoreDefines.h"

#include <GL/glew.h>

#include "enginecore/core/window/BaseWindow.h"

enum class BlendMode 
{
    /// @brief Normal blending mode.
    normal,
    /// @brief Additive blending mode.
    addition,
    /// @brief Subtractive blending mode.
    inversion
};

class Flushable 
{
public:
    virtual ~Flushable() = default;

    virtual void flush() const = 0;
};

class Bindable 
{
public:
    virtual ~Bindable() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
};

class DrawContext 
{    
public:
    DrawContext(
        const DrawContext* parent,
        std::weak_ptr<BaseWindow> window
        //Batch2D* g2d
    )
        : m_window(window),
        m_parent(parent),
        m_current_viewport(window.lock()->viewports()[0]->getSize())
        //g2d(g2d),
        //flushable(g2d)
    {
    }
    ~DrawContext();

    //Batch2D* getBatch2D() const;

    [[nodiscard]] DrawContext sub(const Flushable* const flushable = nullptr) const;

    static void setGlBlendMode(const BlendMode& mode);

    void setViewport(const glm::uvec2& viewport);
    void setFramebuffer(const Bindable* const fbo);
    void setDepthMask(const bool& flag);
    void setDepthTest(const bool& flag);
    void setCullFace(const bool& flag);
    void setBlendMode(const BlendMode& mode);
    void setScissors(const glm::vec4& area);
    void setLineWidth(const float& width);

private:
    std::weak_ptr<BaseWindow> m_window;
    const DrawContext* m_parent;
    glm::ivec2 m_current_viewport;
    //Batch2D* g2d;
    const Flushable* m_flushable = nullptr;
    const Bindable* m_fbo = nullptr;
    bool m_depth_mask = true;
    bool m_depth_test = false;
    bool m_cull_face = false;
    BlendMode m_blend_mode = BlendMode::normal;
    int m_scissors_count = 0;
    float m_line_width = 1.0f;
};

#endif // !RENDER_DRAWCONTEXT_H_