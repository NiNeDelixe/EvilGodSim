#pragma once
#ifndef SHADER_GLSHADER_H_
#define SHADER_GLSHADER_H_

#include <stdexcept>
#include <memory>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glslcompiler/GLSLCompiler.h>

#include "enginecore/core/CoreDefines.h"
#include "enginecore/interfaces/IAsset.h"

#define DECLARE_UNIFORM_INT_FUNCTIONS \
void uniform(const std::string& name, const int& value) { \
    glUniform1i(getUniformLocation(name), value); \
} \
void uniform(const std::string& name, const int& value1, const int& value2) { \
    glUniform2i(getUniformLocation(name), value1, value2); \
} \
void uniform(const std::string& name, const int& value1, const int& value2, const int& value3) { \
    glUniform3i(getUniformLocation(name), value1, value2, value3); \
} \
void uniform(const std::string& name, const int& value1, const int& value2, const int& value3, const int& value4) { \
    glUniform4i(getUniformLocation(name), value1, value2, value3, value4); \
}

#define DECLARE_UNIFORM_FLOAT_FUNCTIONS \
void uniform(const std::string& name, const float& value) { \
    glUniform1f(getUniformLocation(name), value); \
} \
void uniform(const std::string& name, const float& value1, const float& value2) { \
    glUniform2f(getUniformLocation(name), value1, value2); \
} \
void uniform(const std::string& name, const float& value1, const float& value2, const float& value3) { \
    glUniform3f(getUniformLocation(name), value1, value2, value3); \
} \
void uniform(const std::string& name, const float& value1, const float& value2, const float& value3, const float& value4) { \
    glUniform4f(getUniformLocation(name), value1, value2, value3, value4); \
}

class GLShader : public IAsset
{
protected:
	struct shader_deleter
	{
		void operator()(GLuint* shader)
		{
			glDeleteShader(*shader);
			delete shader;
		}
	};

protected:

public:
	GLShader(const GLuint& id);
	GLShader(const GLShader& copy) = delete;
	~GLShader();

protected:
	uint_t getUniformLocation(const std::string& name);

	using glshader = std::unique_ptr<GLuint, shader_deleter>;

	static glshader compileShader(const GLenum& type, const char* source);
	static GLuint linkShader(const GLShader::glshader& vertex, const GLShader::glshader& fragment);

public:
	/// @brief !! use BEFORE uniforms !! 
	virtual void use() const;

	DECLARE_UNIFORM_INT_FUNCTIONS;
	DECLARE_UNIFORM_FLOAT_FUNCTIONS;

	void uniform(const std::string& name, const glm::vec2& value) { uniform(name, value.x, value.y); }
	void uniform(const std::string& name, const glm::ivec2& value) { uniform(name, value.x, value.y); }
	void uniform(const std::string& name, const glm::vec3& value) { uniform(name, value.x, value.y, value.z); }
	void uniform(const std::string& name, const glm::mat4& matrix) 
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	static std::shared_ptr<GLShader> createFromFile(const std::filesystem::path& vertex_filepath,
		const std::filesystem::path& fragment_filepath);

	static std::shared_ptr<GLShader> createFromSource(const std::string& vertex_source,
		const std::string& fragment_source);

public:
	virtual GLuint getId() const { return m_id; }

	static const std::shared_ptr<GLSLCompiler>& getCompiler() { return m_compiler; }

protected:
	GLuint m_id;
	std::unordered_map<std::string, uint_t> m_uniform_locations;

	static std::shared_ptr<GLSLCompiler> m_compiler;
};


#endif // !SHADER_GLSHADER_H_
