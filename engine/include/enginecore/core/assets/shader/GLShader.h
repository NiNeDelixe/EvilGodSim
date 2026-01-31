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
#include <stdarg.h>

#include <glog/logging.h>

#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glslcompiler/GLSLCompiler.h>

#include "enginecore/core/CoreDefines.h"
#include "enginecore/interfaces/IAsset.h"
#include "enginecore/utils/TypeUtils.h"

#define DECLARE_UNIFORMS(T, suffix) \
    void uniform(const std::string_view& name, const T& v1) \
        { glUniform1##suffix(getUniformLocation(name), v1); } \
    void uniform(const std::string_view& name, const T& v1, const T& v2) \
        { glUniform2##suffix(getUniformLocation(name), v1, v2); } \
    void uniform(const std::string_view& name, const T& v1, const T& v2, const T& v3) \
        { glUniform3##suffix(getUniformLocation(name), v1, v2, v3); } \
    void uniform(const std::string_view& name, const T& v1, const T& v2, const T& v3, const T& v4) \
        { glUniform4##suffix(getUniformLocation(name), v1, v2, v3, v4); }

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
	DISABLE_COPY(GLShader)

public:
	GLShader(const GLuint& id);
	//GLShader(const GLShader& copy) = delete;
	~GLShader();

protected:
	GLint getUniformLocation(const std::string_view& name);

	using glshader = std::unique_ptr<GLuint, shader_deleter>;

	static glshader compileShader(const GLenum& type, const char* source);
	static GLuint linkShader(const GLShader::glshader& vertex, const GLShader::glshader& fragment);

public:
	/// @brief !! use BEFORE uniforms !! 
	virtual void use() const;

	DECLARE_UNIFORMS(float, f)
	DECLARE_UNIFORMS(double, d)
	DECLARE_UNIFORMS(int, i)
	DECLARE_UNIFORMS(unsigned int, ui)

	void uniform(const std::string_view& name, const glm::vec2& value) { uniform(name, value.x, value.y); }
	void uniform(const std::string_view& name, const glm::ivec2& value) { uniform(name, value.x, value.y); }
	void uniform(const std::string_view& name, const glm::vec3& value) { uniform(name, value.x, value.y, value.z); }
	void uniform(const std::string_view& name, const glm::vec4& value) { uniform(name, value.r, value.g, value.b, value.a); }
	void uniform(const std::string_view& name, const glm::mat4& matrix) {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void uniform(const std::string_view& name, const glm::mat3& matrix) {
		glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	static std::shared_ptr<GLShader> createFromFile(const std::filesystem::path& vertex_filepath,
		const std::filesystem::path& fragment_filepath);

	static std::shared_ptr<GLShader> createFromSource(const std::string& vertex_source,
		const std::string& fragment_source);

public:
	virtual GLuint getId() const { return m_id; }
	virtual std::string getName(const GLuint& id) { return std::string(); }

	static const std::shared_ptr<GLSLCompiler>& getCompiler() { return m_compiler; }

protected:
	GLuint m_id;
	std::unordered_map<std::string_view, uint_t> m_uniform_locations;

	static std::shared_ptr<GLSLCompiler> m_compiler;
};


#endif // !SHADER_GLSHADER_H_
