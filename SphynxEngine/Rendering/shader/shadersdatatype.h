#ifndef SHADERSDATATYPES_H_
#define SHADERSDATATYPES_H_

#include "glad/glad.h"

// =============================================================================
// shaderDataType enum
// =============================================================================
enum class shaderDataType
{None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool};

// =============================================================================
// ShaderDataTypeSize
// =============================================================================
constexpr GLsizei shaderDataTypeSize(shaderDataType type)
{
    switch(type)
    {
        case shaderDataType::Float: return 4;
        case shaderDataType::Float2: return 4 * 2;
        case shaderDataType::Float3: return 4 * 3;
        case shaderDataType::Float4: return 4 * 4;
        case shaderDataType::Mat3: return 4 * 3 * 3;
        case shaderDataType::Mat4: return 4 * 4 * 4;
        case shaderDataType::Int: return 4;
        case shaderDataType::Int2: return 4 * 2;
        case shaderDataType::Int3: return 4 * 3;
        case shaderDataType::Int4: return 4 * 4;
        case shaderDataType::Bool: return 1;
        case shaderDataType::None: return 0;
    }

    return 0;
}

constexpr GLenum shaderDataTypeToOpenGLBaseType(shaderDataType type)
{
    switch (type)
    {
        case shaderDataType::Float: return GL_FLOAT;
        case shaderDataType::Float2: return GL_FLOAT;
        case shaderDataType::Float3: return GL_FLOAT;
        case shaderDataType::Float4: return GL_FLOAT;
        case shaderDataType::Mat3: return GL_FLOAT;
        case shaderDataType::Mat4: return GL_FLOAT;
        case shaderDataType::Int: return GL_INT;
        case shaderDataType::Int2: return GL_INT;
        case shaderDataType::Int3: return GL_INT;
        case shaderDataType::Int4: return GL_INT;
        case shaderDataType::Bool: return GL_INT;
        case shaderDataType::None: return GL_INT;
    }

    return GL_INT;
}

constexpr GLsizei shaderDataTypeComponentCount(shaderDataType type)
{
    switch (type)
    {
        case shaderDataType::Float: return 1;
        case shaderDataType::Float2: return 2;
        case shaderDataType::Float3: return 3;
        case shaderDataType::Float4: return 4;
        case shaderDataType::Mat3: return 3 * 3;
        case shaderDataType::Mat4: return 4 * 4;
        case shaderDataType::Int: return 1;
        case shaderDataType::Int2: return 2;
        case shaderDataType::Int3: return 3;
        case shaderDataType::Int4: return 4;
        case shaderDataType::Bool: return 1;
        case shaderDataType::None: return 0;
    }
    return 0;
}

#endif // SHADERSDATATYPES_H_
