#pragma once
#ifndef WINDOW_VIEWPORT_H_
#define WINDOW_VIEWPORT_H_

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Viewport
{
public:
	Viewport(const GLsizei& width, const GLsizei& height)
		: Viewport(0, 0, width, height) {}

	Viewport(const GLint& x, const GLint& y, const GLsizei& width, const GLsizei& height)
		: m_x(x), m_y(y), m_width(width), m_height(height)
	{
		glViewport(m_x, m_y, m_width, m_height);
	}

	~Viewport() = default;

public:
	glm::vec2 getSizeFloat() const { return { this->m_width, this->m_height }; };
	glm::ivec2 getSize() const { return { this->m_width, this->m_height }; };
	const GLsizei& getHeight() const { return this->m_height; }
	const GLsizei& getWidth() const { return this->m_width; }

private:
	GLint m_x;
	GLint m_y;

	GLsizei m_width;
	GLsizei m_height;
};


#endif // !WINDOW_VIEWPORT_H_