#include "enginecore/core/assets/shader/GLShader.h"

std::shared_ptr<GLSLCompiler> GLShader::m_compiler = std::make_shared<GLSLCompiler>();

GLShader::GLShader(const GLuint& id)
	: m_id(id)
{
}

GLShader::~GLShader()
{
	glDeleteProgram(m_id);
}

GLint GLShader::getUniformLocation(const std::string& name)
{
    auto found = m_uniform_locations.find(name);
    if (found == m_uniform_locations.end()) 
    {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        if (location == -1)
        {
            LOG_EVERY_N(ERROR, 100) << name << " does not correspond to an active uniform variable in: " << m_id;
            return location;
        }
        m_uniform_locations.try_emplace(name, location);
        return location;
    }
    return found->second;
}

GLShader::glshader GLShader::compileShader(const GLenum& type, const char* source)
{
    GLint success;
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[GL_LOG_LEN];
        glGetShaderInfoLog(shader, GL_LOG_LEN, nullptr, infoLog);
        glDeleteShader(shader);
        throw std::runtime_error(infoLog);
    }

    return glshader(new GLuint(std::forward<GLuint>(shader)), shader_deleter{});
}

GLuint GLShader::linkShader(const GLShader::glshader& vertex, const GLShader::glshader& fragment)
{
    GLint success;
    GLuint id = glCreateProgram();
    glAttachShader(id, *vertex);
    glAttachShader(id, *fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[GL_LOG_LEN];
        glGetProgramInfoLog(id, GL_LOG_LEN, nullptr, infoLog);
        throw std::runtime_error(
            "shader program linking failed:\n" + std::string(infoLog)
        );
    }

    return id;
}

void GLShader::use() const
{
	glUseProgram(m_id);
}

std::shared_ptr<GLShader> GLShader::createFromFile(const std::filesystem::path& vertex_filepath,
    const std::filesystem::path& fragment_filepath)
{
    auto vertex_result = m_compiler->compileShader(vertex_filepath);
    if (!vertex_result.has_value())
    {
        throw std::runtime_error(m_compiler->getError());
    }

    auto fragment_result = m_compiler->compileShader(fragment_filepath);
    if (!fragment_result.has_value())
    {
        throw std::runtime_error(m_compiler->getError());
    }

    std::string vertex_code = vertex_result.value();
    std::string fragment_code = fragment_result.value();

    glshader vertex = nullptr;
    glshader fragment = nullptr;
    try
    {
        vertex = compileShader(GL_VERTEX_SHADER, vertex_code.c_str());
    }
    catch (const std::exception& exc)
    {
        throw std::runtime_error(
            "vertex shader compilation failed (" + vertex_filepath.filename().string() + "):\n" + exc.what());
    }

    try
    {
        fragment = compileShader(GL_FRAGMENT_SHADER, fragment_code.c_str());
    }
    catch (const std::exception& exc)
    {
        throw std::runtime_error(
            "vertex shader compilation failed (" + fragment_filepath.filename().string() + "):\n" + exc.what());
    }

    GLuint id = linkShader(vertex, fragment);
    
    return std::shared_ptr<GLShader>(new GLShader(id));
}

std::shared_ptr<GLShader> GLShader::createFromSource(const std::string& vertex_source, const std::string& fragment_source)
{
    auto vertex_result = m_compiler->compileShader(vertex_source);
    if (!vertex_result.has_value())
    {
        throw std::runtime_error(m_compiler->getError());
    }

    auto fragment_result = m_compiler->compileShader(fragment_source);
    if (!fragment_result.has_value())
    {
        throw std::runtime_error(m_compiler->getError());
    }

    std::string vertex_code = vertex_result.value();
    std::string fragment_code = fragment_result.value();

    glshader vertex = nullptr;
    glshader fragment = nullptr;
    try
    {
        vertex = compileShader(GL_VERTEX_SHADER, vertex_code.c_str());
    }
    catch (const std::exception& exc)
    {
        throw std::runtime_error(
            "vertex shader compilation failed (vertex source):\n" + std::string(exc.what()));
    }

    try
    {
        fragment = compileShader(GL_FRAGMENT_SHADER, fragment_code.c_str());
    }
    catch (const std::exception& exc)
    {
        throw std::runtime_error(
            "vertex shader compilation failed (fragment source):\n" + std::string(exc.what()));
    }

    GLuint id = linkShader(vertex, fragment);

    return std::shared_ptr<GLShader>(new GLShader(id));
}