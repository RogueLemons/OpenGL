#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

// Libraries
#include <glad/glad.h>

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