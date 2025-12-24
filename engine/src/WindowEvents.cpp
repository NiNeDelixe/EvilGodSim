#include "enginecore/core/window/WindowEvents.h"

void BaseWindow::WindowEvents::update()
{
    m_current_frame++;
    m_delta.x = 0.f;
    m_delta.y = 0.f;
    m_scroll = 0;
    m_codepoints.clear();
    m_pressed_keys.clear();
    glfwPollEvents();

    for (auto& entry : m_bindings)
    {
        auto& binding = entry.second;
        if (!binding.m_enable)
        {
            binding.m_state = false;
            continue;
        }
        binding.m_just_change = false;

        bool newstate = false;
        switch (binding.m_type)
        {
        case InputType::keyboard:
            newstate = pressed(binding.m_code);
            break;
        case InputType::mouse:
            newstate = clicked(binding.m_code);
            break;
        }

        if (newstate)
        {
            if (!binding.m_state)
            {
                binding.m_state = true;
                binding.m_just_change = true;
                //binding.onactived.notify(); //TODO:
            }
        }
        else
        {
            if (binding.m_state)
            {
                binding.m_state = false;
                binding.m_just_change = true;
            }
        }
    }
}

bool BaseWindow::WindowEvents::pressed(const Keycode& key) const
{
    int keycode = static_cast<int>(key);
    if (keycode < 0 || keycode >= KEYS_BUFFER_SIZE) 
    {
        return false;
    }
    return m_keys[keycode];
}

bool BaseWindow::WindowEvents::pressed(const int& key) const
{
    return pressed(static_cast<Keycode>(key));
}

bool BaseWindow::WindowEvents::clicked(const Mousecode& code) const
{
    return pressed(
        static_cast<Keycode>(_MOUSE_KEYS_OFFSET + static_cast<int>(code))
    );
}

bool BaseWindow::WindowEvents::clicked(const int& code) const
{
    return clicked(static_cast<Mousecode>(code));
}

void BaseWindow::WindowEvents::setKey(const int& key, const bool& b)
{
    m_keys[key] = b;
    m_frames[key] = m_current_frame;
}

void BaseWindow::WindowEvents::setButton(const int& button, const bool& b)
{
    setKey(_MOUSE_KEYS_OFFSET + button, b);
}

void BaseWindow::WindowEvents::setCursorPosition(const float& xpos, const float& ypos)
{
    if (m_cursor_drag)
    {
        m_delta.x += xpos - m_cursor.x;
        m_delta.y += ypos - m_cursor.y;
    }
    else
    {
        m_cursor_drag = true;
    }
    m_cursor.x = xpos;
    m_cursor.y = ypos;
}

bool BaseWindow::WindowEvents::isCursorLocked() const
{
    return m_cursor_locked;
}

void BaseWindow::WindowEvents::toggleLockCursor()
{
    m_cursor_drag = false;
    if (m_cursor_locked) 
    {
        glfwSetInputMode(m_base_window.m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else 
    {
        glfwSetInputMode(m_base_window.m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    m_cursor_locked = !m_cursor_locked;
}

void BaseWindow::WindowEvents::lockCursor(const bool& state)
{
    m_cursor_drag = false;
    if (!state)
    {
        glfwSetInputMode(m_base_window.m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(m_base_window.m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    m_cursor_locked = state;
}

void BaseWindow::WindowEvents::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    BaseWindow* handler = static_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
    std::shared_ptr<BaseWindow::WindowEvents> events = handler->events();

    if (key == GLFW_KEY_UNKNOWN)
        return;
    if (action == GLFW_PRESS)
    {
        events->setKey(key, true);
        events->m_pressed_keys.push_back(static_cast<Keycode>(key));
    }
    else if (action == GLFW_RELEASE)
    {
        events->setKey(key, false);
    }
    else if (action == GLFW_REPEAT)
    {
        events->m_pressed_keys.push_back(static_cast<Keycode>(key));
    }

    EngiApp->events().invoke(EVENT_NAMESPACE::KeyEvent(InputType::keyboard, key, scancode, action, mode));
}

void BaseWindow::WindowEvents::mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
    BaseWindow* handler = static_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
    std::shared_ptr<BaseWindow::WindowEvents> events = handler->events();

    events->setButton(button, action == GLFW_PRESS);
    EngiApp->events().invoke(EVENT_NAMESPACE::KeyEvent(InputType::mouse, button, 0, action, mode));
}

void BaseWindow::WindowEvents::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    BaseWindow* handler = static_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
    std::shared_ptr<BaseWindow::WindowEvents> events = handler->events();

    events->setCursorPosition(static_cast<float>(xpos), static_cast<float>(ypos));
    EngiApp->events().invoke(EVENT_NAMESPACE::MouseMoveEvent(xpos, ypos));
}

void BaseWindow::WindowEvents::windowSizeCallback(GLFWwindow* window, int width, int height)
{
    BaseWindow* handler = static_cast<BaseWindow*>(glfwGetWindowUserPointer(window));

    if (width && height)
    {
        if (handler->isFocused())
        {
            handler->m_viewports[0] = std::make_shared<Viewport>(width, height);
            handler->m_width = width;
            handler->m_height = height;
        }

        if (!handler->isFullscreen() && !handler->isMaximized())
        {
            handler->m_display_settings.lock()->width.set(width);
            handler->m_display_settings.lock()->height.set(height);
        }
    }
    //handler->resetScissor();
}

void BaseWindow::WindowEvents::glfwErrorCallback(int error_code, const char* error_descrition)
{
    LOG(ERROR) << "gl_error: " << error_descrition;
}

void GLAPIENTRY BaseWindow::WindowEvents::glMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
    {
        return;
    }
    if (!BuildConfig.IS_DEBUG_BUILD && severity != GL_DEBUG_SEVERITY_HIGH)
    {
        return;
    }

    LOG(ERROR) << "GL: " << ENGINE_NAMESPACE::UTILS_NAMESPACE::gl::error_name(type) << " : "
        << ENGINE_NAMESPACE::UTILS_NAMESPACE::gl::severity_name(severity) << ": " << message;
}

void BaseWindow::WindowEvents::characterCallback(GLFWwindow* window, unsigned int codepoint)
{
    BaseWindow* handler = static_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
    std::shared_ptr<BaseWindow::WindowEvents> events = handler->events();

    events->m_codepoints.push_back(codepoint);
}

void BaseWindow::WindowEvents::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    BaseWindow* handler = static_cast<BaseWindow*>(glfwGetWindowUserPointer(window));
    std::shared_ptr<BaseWindow::WindowEvents> events = handler->events();

    events->m_scroll += yoffset;
}