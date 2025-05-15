#pragma once
#ifndef UTILS_GLUTILS_H_
#define UTILS_GLUTILS_H_

#include <GL/glew.h>

#include "enginecore/core/CoreDefines.h"
#include "enginecore/core/assets/texture/Texture.h"

namespace UTILS_NAMESPACE 
{
    namespace gl
    {
        /// @brief Vertex attribute info
        struct VertexAttribute
        {
            enum class Type
            {
                FLOAT,
                INT, UNSIGNED_INT,
                SHORT, UNSIGNED_SHORT,
                BYTE, UNSIGNED_BYTE,
                PADDING
            };

            Type type = Type::FLOAT;
            bool normalized = false;
            int8_t count = 0;

            [[nodiscard]] constexpr uint32_t size() const
            {
                switch (type)
                {
                case Type::FLOAT:
                    return count * sizeof(float);
                case Type::UNSIGNED_INT:
                    return count * sizeof(uint32_t);
                case Type::INT:
                    return count * sizeof(int32_t);
                case Type::UNSIGNED_SHORT:
                    return count * sizeof(uint16_t);
                case Type::SHORT:
                    return count * sizeof(int16_t);
                case Type::UNSIGNED_BYTE:
                    return count * sizeof(uint8_t);
                case Type::BYTE:
                    return count * sizeof(int8_t);
                case Type::PADDING:
                    return count;
                }
                return 0;
            }
        };

        inline GLenum to_glenum(const VertexAttribute::Type& type)
        {
            using Type = VertexAttribute::Type;
            switch (type)
            {
            case Type::FLOAT:
                return GL_FLOAT;
            case Type::UNSIGNED_INT:
                return GL_UNSIGNED_INT;
            case Type::INT:
                return GL_INT;
            case Type::UNSIGNED_SHORT:
                return GL_UNSIGNED_SHORT;
            case Type::SHORT:
                return GL_SHORT;
            case Type::UNSIGNED_BYTE:
                return GL_UNSIGNED_BYTE;
            case Type::BYTE:
                return GL_BYTE;
            }
            return 0;
        }



        inline GLenum to_glenum(const ImageData::ImageFormat& imageFormat)
        {
            switch (imageFormat) 
            {
            case ImageData::ImageFormat::rgb888: return GL_RGB;
            case ImageData::ImageFormat::rgba8888: return GL_RGBA;
            default:
                return 0;
            }
        }

        inline static const char* error_name(const int& error) 
        {
            switch (error) 
            {
            case GL_DEBUG_TYPE_ERROR: 
                return "ERROR";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: 
                return "DEPRECATED_BEHAVIOR";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: 
                return "UNDEFINED_BEHAVIOR";
            case GL_DEBUG_TYPE_PORTABILITY: 
                return "PORTABILITY";
            case GL_DEBUG_TYPE_PERFORMANCE: 
                return "PERFORMANCE";
            case GL_DEBUG_TYPE_OTHER: 
                return "OTHER";
            }
            return "UNKNOWN";
        }

        inline static const char* severity_name(const int& severity)
        {
            switch (severity) 
            {
            case GL_DEBUG_SEVERITY_LOW: 
                return "LOW";
            case GL_DEBUG_SEVERITY_MEDIUM: 
                return "MEDIUM";
            case GL_DEBUG_SEVERITY_HIGH: 
                return "HIGH";
            case GL_DEBUG_SEVERITY_NOTIFICATION: 
                return "NOTIFICATION";
            }
            return "UNKNOWN";
        }



        /*inline GLenum to_glenum(DrawPrimitive primitive) {
            static const GLenum primitives[]{
                GL_POINTS,
                GL_LINES,
                GL_TRIANGLES
            };
            return primitives[static_cast<int>(primitive)];
        }*/
    }
    
}

#endif // !UTILS_GLUTILS_H_