#pragma once
#ifndef WINDOW_WINDOWEVENTS_H_
#define WINDOW_WINDOWEVENTS_H_

#include <memory>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <BuildConfig.h>

#include "enginecore/core/window/BaseWindow.h"
#include "enginecore/core/window/Input.h"

#include "enginecore/utils/GLUtils.h"

#include "enginecore/core/EngineCoreApplication.h"

class BaseWindow::WindowEvents
{
public:
	WindowEvents(BaseWindow& bw)
		: m_base_window(bw)
	{ }
	~WindowEvents() = default;

public:
	void update();

	bool pressed(const Keycode& key) const;
	bool pressed(const int& key) const;
	bool clicked(const Mousecode& code) const;
	bool clicked(const int& code) const;

public:
	const glm::vec2& getCursorPos() const { return m_cursor; }
	const glm::vec2& getCursorDelta() const { return m_delta; }

public:
	void setKey(const int& key, const bool& b);
	void setButton(const int& button, const bool& b);
	void setCursorPosition(const float& xpos, const float& ypos);

public:
	bool isCursorLocked() const;
	void toggleLockCursor();
	void lockCursor(const bool& state);

public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void characterCallback(GLFWwindow* window, unsigned int codepoint);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	static void glfwErrorCallback(int error_code, const char* error_descrition);
	static void GLAPIENTRY glMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

protected:
	BaseWindow& m_base_window;

	std::unordered_map<std::string, Binding> m_bindings;

	std::vector<uint_t> m_codepoints = {};
	std::vector<Keycode> m_pressed_keys = {};
	double m_scroll = 0;

	bool m_keys[KEYS_BUFFER_SIZE] = {};
	uint_t m_frames[KEYS_BUFFER_SIZE] = {};
	uint_t m_current_frame = 0;
	glm::vec2 m_delta = {};
	glm::vec2 m_cursor = {};
	bool m_cursor_drag = false;
	bool m_cursor_locked = false;
};


#endif // !WINDOW_WINDOWEVENTS_H_