#include "enginecore/core/graphics/render/DrawContext.h"

DrawContext::~DrawContext()
{
    if (m_flushable)
    {
        m_flushable->flush();
    }

    while (m_scissors_count--)
    {
        m_window.lock()->popScissor();
    }

    if (m_parent == nullptr)
        return;

    if (m_fbo != m_parent->m_fbo)
    {
        if (m_fbo)
        {
            m_fbo->unbind();
        }
        if (m_parent->m_fbo)
        {
            m_parent->m_fbo->bind();
        }
    }

    glViewport(0, 0, m_parent->m_current_viewport.x, m_parent->m_current_viewport.y);

    if (m_depth_mask != m_parent->m_depth_mask)
    {
        glDepthMask(m_parent->m_depth_mask);
    }
    if (m_depth_test != m_parent->m_depth_test)
    {
        if (m_depth_test) 
            glDisable(GL_DEPTH_TEST);
        else 
            glEnable(GL_DEPTH_TEST);
    }
    if (m_cull_face != m_parent->m_cull_face) 
    {
        if (m_cull_face) 
            glDisable(GL_CULL_FACE);
        else 
            glEnable(GL_CULL_FACE);
    }
    if (m_blend_mode != m_parent->m_blend_mode) 
    {
        DrawContext::setBlendMode(m_parent->m_blend_mode);
    }
    if (m_line_width != m_parent->m_line_width) 
    {
        glLineWidth(m_parent->m_line_width);
    }
}

DrawContext DrawContext::sub(const Flushable* const flushable) const
{
    auto ctx = DrawContext(*this);
    ctx.m_parent = this;
    ctx.m_flushable = flushable;
    ctx.m_scissors_count = 0;
    /*if (auto batch2D = dynamic_cast<Batch2D*>(flushable)) {
        ctx.g2d = batch2D;
    }*/
    return ctx;
}

void DrawContext::setGlBlendMode(const BlendMode& mode)
{
    switch (mode) 
    {
    case BlendMode::normal:
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        break;
    case BlendMode::addition:
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        break;
    case BlendMode::inversion:
        glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
        break;
    }
}

void DrawContext::setViewport(const glm::uvec2& viewport)
{
    this->m_current_viewport = viewport;
    glViewport(0, 0, viewport.x, viewport.y);
}

void DrawContext::setFramebuffer(const Bindable* const fbo)
{
    if (this->m_fbo == fbo)
        return;
    this->m_fbo = fbo;
    if (fbo) 
    {
        fbo->bind();
    }
}

void DrawContext::setDepthMask(const bool& flag)
{
    if (m_depth_mask == flag)
        return;
    m_depth_mask = flag;
    glDepthMask(GL_FALSE + flag);
}

void DrawContext::setDepthTest(const bool& flag)
{
    if (m_depth_test == flag)
        return;
    m_depth_test = flag;
    if (flag) 
    {
        glEnable(GL_DEPTH_TEST);
    }
    else 
    {
        glDisable(GL_DEPTH_TEST);
    }
}

void DrawContext::setCullFace(const bool& flag)
{
    if (m_cull_face == flag)
        return;
    m_cull_face = flag;
    if (flag) 
    {
        glEnable(GL_CULL_FACE);
    }
    else 
    {
        glDisable(GL_CULL_FACE);
    }
}

void DrawContext::setBlendMode(const BlendMode& mode)
{
    if (m_blend_mode == mode)
        return;
    m_blend_mode = mode;
    DrawContext::setBlendMode(mode);
}

void DrawContext::setScissors(const glm::vec4& area)
{
    m_window.lock()->pushScissor(area);
    m_scissors_count++;
}

void DrawContext::setLineWidth(const float& width)
{
    m_line_width = width;
    glLineWidth(width);
}
