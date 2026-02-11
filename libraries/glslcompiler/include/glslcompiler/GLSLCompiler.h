#pragma once
#ifndef GLSLCOMPILER_GLSSLCOMPILER_H_
#define GLSLCOMPILER_GLSSLCOMPILER_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <regex>
#include <filesystem>
#include <optional>

class GLSLCompiler 
{
public:
    GLSLCompiler();
    ~GLSLCompiler() = default;

    std::optional<std::string> compileShader(const std::string& source);
    std::optional<std::string> compileShader(const std::filesystem::path& file_path);

    std::optional<std::string> linkProgram(const std::string& vertex_shader, const std::string& fragment_shader);

    void addIncludePath(const std::filesystem::path& path);

    const std::string& getError() { return m_error_str; }

private:
    std::optional<std::string> processIncludes(const std::string& source);

    //bool validateGLSL(const std::string& source, const std::string& shaderType, std::string& errors);

private:
    std::vector<std::filesystem::path> m_include_paths;

    std::string m_error_str;
};

#endif // !GLSLCOMPILER_GLSSLCOMPILER_H_