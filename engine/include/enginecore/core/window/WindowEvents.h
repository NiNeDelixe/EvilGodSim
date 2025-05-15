#pragma once
#ifndef WINDOW_WINDOWEVENTS_H_
#define WINDOW_WINDOWEVENTS_H_

#include <memory>

#include <BuildConfig.h>

#include "enginecore/core/window/BaseWindow.h"
#include "enginecore/core/window/Input.h"

#include "enginecore/utils/GLUtils.h"

#include "enginecore/core/EngineCoreApplication.h"

class BaseWindow::WindowEvents
{
public:
	WindowEvents() = default;
	~WindowEvents() = default;

public:
	void update();

	bool pressed(const Keycode& key) const;
	bool pressed(const int& key) const;
	bool clicked(const Mousecode& code) const;
	bool clicked(const int& code) const;

public:
	void setKey(const int& key, const bool& b);
	void setButton(const int& button, const bool& b);
	void setCursorPosition(const float& xpos, const float& ypos);

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void characterCallback(GLFWwindow* window, unsigned int codepoint);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void windowSizeCallback(GLFWwindow* window, int width, int height);
	static void glfwErrorCallback(int error_code, const char* error_descrition);
	static void GLAPIENTRY glMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

private:
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