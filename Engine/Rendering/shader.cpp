//
// Created by anmar on 9/27/2022.
//

#include "shader.h"
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>

/**
 * Prints the contents of the error log to console for programs and shaders.
 * TODO: Make type secure
 * @param type - GL_PROGRAM, GL_(VERTEX/FRAGMENT)_SHADER
 * @param ID
 */
void ivErrorMessage(const GLuint type, const GLuint &ID) {
    if(type == GL_PROGRAM || type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER) {
        int len;
        char* message;
        std::string identifier;
        std::string operation;
        if(type == GL_PROGRAM) {
            glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &len); //Retrieves error log length.
            message = (char*) alloca (len * sizeof(char));//Dynamic stack allocation.
            glGetProgramInfoLog(ID, len, &len, message);
            identifier = "program";
            operation = "link";
        } else {
            glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &len);
            message = (char*) alloca (len * sizeof(char));
            glGetShaderInfoLog(ID, len, &len, message);
            identifier = (type == GL_VERTEX_SHADER)? "vertex" : "fragment";
            identifier += " shader";
            operation = "compile";
        }
        std::cout << "Failed to " << operation << " the " << identifier << std::endl;
        std::cout << message << std::endl;
    } else {
        std::cout << "Invalid GL enum. Must be GL_VERTEX_SHADER, GL_FRAGMENT_SHADER or GL_PROGRAM." << std::endl;
    }
}

/**
 * Inputs plaintext from file into a string. For use with GLSL source files.
 * @param filepath - path to source file
 * @param printToTerminal - prints sourcecode to terminal if set true
 * @return - source code in string format
 */
std::string Shader::fileToString(const std::string &filePath) {
    std::ifstream in(filePath);
    if (in.is_open()) {
        std::stringstream ss;
        ss << in.rdbuf();
        return ss.str();
    } else {
        std::cout << "\n[SHADER FILE ERROR]: failed to open file at path " << filePath << std::endl;
        std::cout << "Empty string returned." << std::endl;
        return {};
    }
}



GLint Shader::getUniformLocation(const std::string &name) {
    if(m_uniformLocations.find(name) != m_uniformLocations.end()) {
        return m_uniformLocations[name];
    } else {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        if(location != -1) {
            m_uniformLocations.insert({name, location});
            return location;
        } else {
            std::cout << "[SHADER ERROR] Invalid uniform name: " << name << std::endl;
            return -1;
        }
    }
}

Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc) {
    compileShader(GL_VERTEX_SHADER, vertexSrc);
    compileShader(GL_FRAGMENT_SHADER, fragmentSrc);
    GLuint program = glCreateProgram();
    glAttachShader(program, m_vertexShader);
    glAttachShader(program, m_fragmentShader);
    glLinkProgram(program);
    int linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if(linked == GL_TRUE) {
        m_shaderProgram = program;
    } else {
        ivErrorMessage(GL_PROGRAM, program);
        glDeleteProgram(program);
    }
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
}


/**
 * Constructs a Shader object from path and filenames for a vertex and fragment shader
 * @param vertexShaderPath
 * @param vertexShaderName
 * @param fragmentShaderPath
 * @param fragmentShaderName
 */
Shader::Shader(const std::string &vertexShaderPath, const std::string &vertexShaderName,
               const std::string &fragmentShaderPath, const std::string &fragmentShaderName ) :
                                        Shader(fileToString(vertexShaderPath + vertexShaderName),
                                               fileToString(fragmentShaderPath + fragmentShaderName))
{};


Shader::~Shader() {
    glDeleteProgram(m_shaderProgram);
}


void Shader::use() const {
        if(m_shaderProgram) {
            glUseProgram(m_shaderProgram);
        } else {
            std::cout << "[Shader object error]: Attempted to bind invalid shader program" << std::endl;
        }
}



void Shader::compileShader(unsigned shaderType, const std::string &shaderSrc) {
    unsigned shader = glCreateShader(shaderType);
    const GLchar* ss = shaderSrc.c_str();
    // target shader for source replacement, nr of elements(can be multiple),
    // pointer to array of pointers(if multiple), array with lengths for each string, or NULL/nullptr.
    // nullptr assumes strings are null terminated.
    glShaderSource(shader, 1, &ss, nullptr );
    // compiles supplied source code associated with input ID
    glCompileShader(shader);

    int compiled;
    // Retrieves compilation status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_TRUE) {
        switch(shaderType) {
            case GL_VERTEX_SHADER  : m_vertexShader = shader  ; break;
            case GL_FRAGMENT_SHADER: m_fragmentShader = shader; break;
            default: break;
        }
    } else {
        ivErrorMessage(shaderType, shader);
        glDeleteShader(shader);
    }
}
