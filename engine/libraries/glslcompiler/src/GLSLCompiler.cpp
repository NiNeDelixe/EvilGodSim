#include "glslcompiler/GLSLCompiler.h"

GLSLCompiler::GLSLCompiler()
{
	m_include_paths.push_back(".");
}

std::optional<std::string> GLSLCompiler::compileShader(const std::string& source_string)
{
    std::string source = source_string;

    std::optional<std::string> processed_result = processIncludes(source);
    if (!processed_result.has_value())
    {
        return {};
    }

    /*if (!validateGLSL(processedSource, shaderType, errors)) {
        return false;
    }*/

    return processed_result.value_or("");
}

std::optional<std::string> GLSLCompiler::compileShader(const std::filesystem::path& file_path)
{
    std::ifstream file(file_path);
    if (!file) 
    {
        m_error_str = "Failed to open file: " + file_path.string();
        return {};
    }

    std::string source((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    std::optional<std::string> processed_result = processIncludes(source);
    if (!processed_result.has_value())
    {
        return {};
    }

    std::string shaderType;
    if (file_path.filename().extension().string().find("v") != std::string::npos) 
    {
        shaderType = "vertex";
    }
    else if (file_path.filename().extension().string().find("f") != std::string::npos) 
    {
        shaderType = "fragment";
    }
    else 
    {
        m_error_str = "Unknown shader type (file extension should be .vert or .frag)";
        return {};
    }

    /*if (!validateGLSL(processedSource, shaderType, errors)) {
        return false;
    }*/

    return processed_result.value_or("");
}

std::optional<std::string> GLSLCompiler::linkProgram(const std::string& vertex_shader, const std::string& fragment_shader)
{
    return std::optional<std::string>();
}

void GLSLCompiler::addIncludePath(const std::filesystem::path& path)
{
	m_include_paths.push_back(path);
}

std::optional<std::string> GLSLCompiler::processIncludes(const std::string& source)
{
    std::istringstream stream(source);
    std::string line;
    std::ostringstream output;
    std::regex includeRegex(R"(^\s*#include\s+[\"<](.+?)[\">]\s*)");

    while (std::getline(stream, line)) 
    {
        std::smatch match;
        if (std::regex_match(line, match, includeRegex)) 
        {
            std::string includeFile = match[1].str();
            bool found = false;

            for (const auto& path : m_include_paths) 
            {
                std::filesystem::path fullPath = std::filesystem::path(path) / includeFile;
                if (std::filesystem::exists(fullPath)) 
                {
                    std::ifstream includeStream(fullPath);
                    if (includeStream) 
                    {
                        std::string includeContent((std::istreambuf_iterator<char>(includeStream)),
                            std::istreambuf_iterator<char>());

                        std::optional<std::string> processedInclude = processIncludes(includeContent);
                        if (!processedInclude.has_value())
                        {
                            return {};
                        }

                        output << processedInclude.value_or("") << "\n";
                        found = true;
                        break;
                    }
                }
            }

            if (!found) 
            {
                m_error_str = "Could not find include file: " + includeFile;
                return {};
            }
        }
        else 
        {
            output << line << "\n";
        }
    }

    return output.str();
}
