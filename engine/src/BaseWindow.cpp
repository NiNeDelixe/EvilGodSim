#include "enginecore/core/window/BaseWindow.h"

#include "enginecore/core/window/WindowEvents.h" //FIXME: move to header

BaseWindow::BaseWindow(const std::weak_ptr<DisplaySettings>& settings, const std::string& window_title)
    : m_display_settings(settings), m_title(window_title), m_events(std::make_shared<WindowEvents>(*this))
{
    std::shared_ptr<DisplaySettings> display_settings = m_display_settings.lock();
    int width = static_cast<int>(display_settings->width.get());
    int height = static_cast<int>(display_settings->height.get());

    m_height = height;
    m_width = width;

    glfwSetErrorCallback(BaseWindow::WindowEvents::glfwErrorCallback);
    if (glfwInit() == GLFW_FALSE)
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef E_OS_DARWIN
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#else
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, static_cast<int>(display_settings->samples.get()));

    GLFWwindow* window = glfwCreateWindow(width, height, m_title.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    m_window = window;
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum glewErr = glewInit();
    if (glewErr != GLEW_OK)
    {
        if (glewErr == GLEW_ERROR_NO_GLX_DISPLAY)
        {
            LOG(WARNING) << "glewInit() returned GLEW_ERROR_NO_GLX_DISPLAY; ignored";
        }
        else
        {
            LOG(ERROR) << "failed to initialize GLEW:\n" << glewGetErrorString(glewErr);
        }
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(m_events->glMessageCallback, 0);

    this->m_viewports[0] = std::make_shared<Viewport>(width, height);

    glClearColor(0.0f, 0.0f, 0.0f, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint maxTextureSize[1]{ static_cast<GLint>(Texture::MAX_RESOLUTION) };
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, maxTextureSize);
    if (maxTextureSize[0] > 0) 
    {
        Texture::MAX_RESOLUTION = maxTextureSize[0];
        LOG(INFO) << "Max texture size is " << Texture::MAX_RESOLUTION;
    }

    glfwSetKeyCallback(window, WindowEvents::keyCallback);
    glfwSetMouseButtonCallback(window, WindowEvents::mouseButtonCallback);
    glfwSetCursorPosCallback(window, WindowEvents::cursorPositionCallback);
    glfwSetWindowSizeCallback(window, WindowEvents::windowSizeCallback);
    glfwSetCharCallback(window, WindowEvents::characterCallback);
    glfwSetScrollCallback(window, WindowEvents::scrollCallback);

    /*observers_keeper = util::ObjectsKeeper();
    observers_keeper.keepAlive(display_settings->fullscreen.observe(
        [](bool value) {
            if (value != isFullscreen()) {
                toggleFullscreen();
            }
        },
        true
    ));*/

    setMaxFramerate(display_settings->framerate.get());

    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    LOG(INFO) << "GL Vendor: " << reinterpret_cast<const char*>(vendor);
    LOG(INFO) << "GL Renderer: " << reinterpret_cast<const char*>(renderer);
    LOG(INFO) << "GLFW: " << glfwGetVersionString();

    glm::vec2 scale = glm::vec2();
    glfwGetMonitorContentScale(glfwGetPrimaryMonitor(), &scale.x, &scale.y);
    LOG(INFO) << "Monitor content scale x: " << scale.x << " y: " << scale.y;

    //input_util::initialize();

    //for (int i = 0; i <= static_cast<int>(CursorShape::LAST); i++) {
    //    int cursor = GLFW_ARROW_CURSOR + i;
    //    // GLFW 3.3 does not support some cursors
    //    if (GLFW_VERSION_MAJOR <= 3 && GLFW_VERSION_MINOR <= 3 && cursor > GLFW_VRESIZE_CURSOR) {
    //        break;
    //    }
    //    standard_cursors[i] = glfwCreateStandardCursor(cursor);
    //}

    glfwSetWindowUserPointer(window, this);

    m_window = window;
}

BaseWindow::~BaseWindow()
{
	glfwDestroyWindow(m_window);
}

void BaseWindow::update()
{
    glfwSwapBuffers(m_window);
    resetScissor();
    if (this->m_max_framerate > 0) 
    {
        auto elapsed_time = time() - this->m_prev_swap;
        auto frame_time = 1.0 / this->m_max_framerate;
        if (elapsed_time < frame_time)
        {
            UTILS_NAMESPACE::time::sleep(static_cast<size_t>((frame_time - elapsed_time) * 1000));
        }
    }
    this->m_prev_swap = time();
}

void BaseWindow::setMaxFramerate(const size_t& fps)
{
    glfwMakeContextCurrent(m_window);
    if ((fps != -1) != (this->m_max_framerate != -1)) 
    {
        glfwSwapInterval(fps == -1);
    }
    this->m_max_framerate = fps;
}

void BaseWindow::clear()
{
    glfwMakeContextCurrent(m_window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BaseWindow::clearDepth()
{
    glfwMakeContextCurrent(m_window);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void BaseWindow::setBackgroundColor(const glm::vec3& color)
{
    glfwMakeContextCurrent(m_window);
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void BaseWindow::setBackgroundColor(const glm::vec4& color)
{
    glfwMakeContextCurrent(m_window);
    glClearColor(color.r, color.g, color.b, color.a);
}

void BaseWindow::pushScissor(const glm::vec4& area)
{
    if (m_scissor_stack.empty()) 
    {
        glEnable(GL_SCISSOR_TEST);
    }
    m_scissor_stack.push(m_scissor_area);

    glm::vec4 new_area = area;

    new_area.z += glm::ceil(new_area.x);
    new_area.w += glm::ceil(new_area.y);

    new_area.x = glm::max(new_area.x, m_scissor_area.x);
    new_area.y = glm::max(new_area.y, m_scissor_area.y);

    new_area.z = glm::min(new_area.z, m_scissor_area.z);
    new_area.w = glm::min(new_area.w, m_scissor_area.w);

    if (new_area.z < 0.0f || new_area.w < 0.0f)
    {
        glScissor(0, 0, 0, 0);
    }
    else 
    {
        glScissor(
            new_area.x,
            m_height - new_area.w,
            std::max(0, static_cast<int>(glm::ceil(new_area.z - new_area.x))),
            std::max(0, static_cast<int>(glm::ceil(new_area.w - new_area.y)))
        );
    }
    m_scissor_area = new_area;
}

void BaseWindow::resetScissor()
{
    m_scissor_area = glm::vec4(0.0f, 0.0f, m_width, m_height);
    m_scissor_stack = std::stack<glm::vec4>();
    glDisable(GL_SCISSOR_TEST);
}

void BaseWindow::popScissor()
{
    if (m_scissor_stack.empty()) 
    {
        LOG(WARNING) << "extra popScissor call";
        return;
    }
    glm::vec4 area = m_scissor_stack.top();
    m_scissor_stack.pop();
    if (area.z < 0.0f || area.w < 0.0f) 
    {
        glScissor(0, 0, 0, 0);
    }
    else 
    {
        glScissor(
            area.x,
            m_height - area.w,
            std::max(0, static_cast<int>(area.z - area.x)),
            std::max(0, static_cast<int>(area.w - area.y))
        );
    }
    if (m_scissor_stack.empty()) 
    {
        glDisable(GL_SCISSOR_TEST);
    }
    m_scissor_area = area;
}

etime_t BaseWindow::time()
{
    glfwMakeContextCurrent(m_window);
    return glfwGetTime();
}