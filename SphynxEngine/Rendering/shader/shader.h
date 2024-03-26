//
// Created by andre on 27.09.22.
//

#ifndef PROG2002_SHADER_H
#define PROG2002_SHADER_H

#include <string>
#include <iostream>
#include "shadersdatatype.h"
#include <unordered_map>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"


/**
 * Class handling the compilation and creation of a shader program
 * using provided GLSL shader source code
 */
class Shader {
private:
    unsigned m_shaderProgram {};    ///< Shader program ID.
    unsigned m_vertexShader  {};     ///< Vertex shader ID.
    unsigned m_fragmentShader{};   ///< Fragment shader ID.
    std::unordered_map<std::string, GLint> m_uniformLocations; ///< Map containing ID of valid uniforms

    /// Compiles shader from source code
    void compileShader(unsigned shaderType, const std::string &shaderSrc);
    std::string fileToString( const std::string &filePath);
    GLint getUniformLocation(const std::string &name);

public:
    /**
     * Constructs a shader program from a vertex shader source
     * and fragment shader source
     * @param vertexSrc - vertex shader source code
     * @param fragmentSrc - fragment shader source code
     */
    Shader(const std::string &vertexSrc, const std::string &fragmentSrc);

    Shader(const std::string &vertexShaderPath, const std::string &vertexShaderName, const std::string &fragmentShaderPath, const std::string &fragmentShaderName);

    /**
     * deletes program before going out of scope
     */
    ~Shader();


    /**
     * Binds shader program if valid
     */
    void use() const;


    /**
     * Unbinds any shader in use
     */
    inline static void unbindShader() { glUseProgram(0); }


    //*****************************************************************************************
    //
    //      UNIFORM UPLOADS
    //
    //*****************************************************************************************


    /**
     * Allows upload of uniform of GLSL type vec2
     * @param name - name of uniform
     * @param vector - glm::vec2
     */
    inline void uploadUniformFloat2(const std::string &name, const glm::vec2 &vector) {
        glUniform2f(getUniformLocation(name), vector[0], vector[1]);
    }

    /**
     * Allows upload of uniform of GLSL type float
     * @param name - uniform name
     * @param f - float data
     */
    inline void uploadUniformFloat(const std::string &name, const float &value) {
        glUniform1f(getUniformLocation(name), value);
    }

    /**
     * Allows upload of uniform of GLSL type vec3
     * @param name
     * @param value
     */
    inline void uploadUniformVec3(const std::string &name, const glm::vec3 &value) {
        glUniform3f(getUniformLocation(name), value[0], value[1], value[2]);
    }

    /**
     * Allows upload of uniform og GLSL type mat3
     * @param name - name of uniform
     * @param matrix - 3x3 glm matrix
     */
    inline void uploadUniformMat3(const std::string &name, const glm::mat3 &matrix) {
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    /**
     * Allows upload of uniform og GLSL type mat4
     * @param name - name of uniform
     * @param matrix - 4x4 glm matrix
     */
    inline void uploadUniformMat4(const std::string &name, const glm::mat4 &matrix) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    /**
     * Allows upload of uniform of GLSL type Int/Bool
     * @param name - name of uniform
     * @param value - int / bool value
     */
    inline void uploadUniformInt(const std::string &name, const int &value) {
        glUniform1i(getUniformLocation(name), value);
    }

};


#endif //PROG2002_SHADER_H
