#pragma once
#ifndef RENDER_DRAWCONTEXT_H_
#define RENDER_DRAWCONTEXT_H_

#include "enginecore/core/CoreDefines.h"

#include <GL/glew.h>

#include "enginecore/core/window/BaseWindow.h"
#include "enginecore/core/graphics/render/Batch2D.h"

#include "enginecore/interfaces/IBindable.h"
#include "enginecore/interfaces/IFlushable.h"

enum class BlendMode 
{
    /// @brief Normal blending mode.
    normal,
    /// @brief Additive blending mode.
    addition,
    /// @brief Subtractive blending mode.
    inversion
};

class DrawContext 
{    
public:
    DrawContext(const DrawContext* parent, std::weak_ptr<BaseWindow> window, std::shared_ptr<Batch2D> g2d);
    ~DrawContext();

private:
    static void setGlBlendMode(const BlendMode& mode);

public:
    GETTER(std::shared_ptr<Batch2D>, m_g2d, Batch2D)

public:
    [[nodiscard]] DrawContext sub(std::shared_ptr<IFlushable> flushable = nullptr) const;


    void setViewport(const glm::uvec2& viewport);
    void setFramebuffer(const IBindable* const fbo);
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
    std::shared_ptr<Batch2D> m_g2d;
    std::weak_ptr<IFlushable> m_flushable;
    const IBindable* m_fbo = nullptr;
    bool m_depth_mask = true;
    bool m_depth_test = false;
    bool m_cull_face = false;
    BlendMode m_blend_mode = BlendMode::normal;
    int m_scissors_count = 0;
    float m_line_width = 1.0f;
};

#endif // !RENDER_DRAWCONTEXT_H_