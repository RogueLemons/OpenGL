#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

// Libraries
#include "Core/glad/glad.h"
#include <glm/glm.hpp>

class Shader
{
public:

    GLuint ID;
    // constructor generates the shader on the fly
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        GLuint vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, ShaderType::Vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, ShaderType::Fragment);

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, ShaderType::Program);

        // 3. delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    ~Shader() {
        glDeleteProgram(ID);
    }

    // activate the shader
    void use()
    {
        glUseProgram(ID);
    }

    // utility uniform functions
    void setBool(const std::string& name, bool value) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniform1i(uniLoc, static_cast<int>(value));
    }
    void setInt(const std::string& name, int value) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniform1i(uniLoc, value);
    }
    void setFloat(const std::string& name, float value) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniform1f(uniLoc, value);
    }
    void setVec2(const std::string& name, const glm::vec2& value) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniform2fv(uniLoc, 1, &value[0]);
    }
    void setVec2(const std::string& name, float x, float y) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniform2f(uniLoc, x, y);
    }
    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniform3fv(uniLoc, 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniform3f(uniLoc, x, y, z);
    }
    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniform4fv(uniLoc, 1, &value[0]);
    }
    void setVec4(const std::string& name, float x, float y, float z, float w) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniform4f(uniLoc, x, y, z, w);
    }
    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniformMatrix2fv(uniLoc, 1, GL_FALSE, &mat[0][0]);
    }
    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniformMatrix3fv(uniLoc, 1, GL_FALSE, &mat[0][0]);
    }
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        auto uniLoc = glGetUniformLocation(ID, name.c_str());
        assert(uniLoc != -1 && "Shader uniform does not exist.");
        glUniformMatrix4fv(uniLoc, 1, GL_FALSE, &mat[0][0]);        // or use glm::value_ptr(model)
    }

private:

    enum ShaderType {
        Program,
        Vertex,
        Fragment,
    };

    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(GLuint shader, ShaderType type)
    {
        int success;
        const int infoLogLength = 1024;
        char infoLog[infoLogLength];
        if (type != ShaderType::Program)
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, infoLogLength, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};