#pragma once
#ifndef WINDOW_BASEWINDOW_H_
#define WINDOW_BASEWINDOW_H_

#include <stdexcept>
#include <string>
#include <vector>
#include <stack>
#include <deque>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glog/logging.h>

#include "enginecore/core/CoreDefines.h"

#include "enginecore/core/Settings_p.h"

#include "enginecore/core/window/Input.h"
#include "enginecore/core/window/Viewport.h"

#include "enginecore/core/assets/texture/Texture.h"

#include "enginecore/utils/platform/SystemDetection.h"
#include "enginecore/utils/TimeUtils.h"

#ifdef MAX
#undef MAX
#endif // MAX

#ifdef max
#undef max
#endif // max

#ifdef MIN
#undef MIN
#endif // MIN

#ifdef min
#undef min
#endif // min


class BaseWindow
{
public:
    class WindowEvents;

private:
    DISABLE_COPY(BaseWindow)

public:
    BaseWindow(const std::weak_ptr<DisplaySettings>& settings, const std::string& window_title);
    ~BaseWindow();

public:
    void update();
    bool shouldClose() const { return glfwWindowShouldClose(m_window); }
    void setShouldClose(const bool& state) { glfwSetWindowShouldClose(m_window, state); }
    void setMaxFramerate(const size_t& fps);

public:
    const bool& isFullscreen() const { return m_in_fullscreen; }
    bool isMaximized() const { return glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED); };
    bool isFocused() const { return glfwGetWindowAttrib(m_window, GLFW_FOCUSED); }
    bool isIconified() const { return glfwGetWindowAttrib(m_window, GLFW_ICONIFIED); }

public:
    void clear();
    void clearDepth();
    void setBackgroundColor(const glm::vec3& color);
    void setBackgroundColor(const glm::vec4& color);

public:
    void pushScissor(const glm::vec4& area);
    void resetScissor();
    void popScissor();

public:
    const std::deque<std::shared_ptr<Viewport>>& viewports() const { return this->m_viewports; }
    GLFWwindow* const getGLFWWindow() const { return this->m_window; }
    etime_t time();

public:
    const std::shared_ptr<WindowEvents>& events() { return this->m_events; }

protected:
    GLFWwindow* m_window;
    std::shared_ptr<WindowEvents> m_events;

    integer_t m_width;
    integer_t m_height;
    int m_pos_x;
    int m_pos_y;
    std::string m_title;

    std::deque<std::shared_ptr<Viewport>> m_viewports = std::deque<std::shared_ptr<Viewport>>(1);

    std::weak_ptr<DisplaySettings> m_display_settings;

    bool m_in_fullscreen;
    int m_max_framerate;
    double m_prev_swap;

    std::stack<glm::vec4> m_scissor_stack = {};
    glm::vec4 m_scissor_area = {};
};


#endif // !WINDOW_BASEWINDOW_H_