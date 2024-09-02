#include "Shader.h"
#include "Utility.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Libraries
#include <glad/glad.h>

enum ShaderType {
    Program,
    Vertex,
    Fragment,
};
// utility function for checking shader compilation/linking errors.
static void CheckCompileErrors(GLuint shader, ShaderType type)
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

namespace Charis {

	Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader, InputType inputType)
	{
        // 1. retrieve the vertex/fragment source code
        std::string vertexCode;
        std::string fragmentCode;

		if (inputType == InCode) {
			vertexCode = vertexShader;
			fragmentCode = fragmentShader;
		}
		else if (inputType == Filepath) {
            // retrieve the vertex/fragment source code from filePath
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            // ensure ifstream objects can throw exceptions:
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try
            {
                // open files
                vShaderFile.open(vertexShader);
                fShaderFile.open(fragmentShader);
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
		}
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, ShaderType::Vertex);

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, ShaderType::Fragment);

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertex);
        glAttachShader(m_ID, fragment);
        glLinkProgram(m_ID);
        CheckCompileErrors(m_ID, ShaderType::Program);

        // 3. delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ID);
	}

    void Shader::Draw(const ModelComponent& model) const
    {
        glUseProgram(m_ID);
        glBindVertexArray(model.m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, model.m_VBO);

        if (model.m_UsingIBO) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.m_IBO);
            glDrawElements(GL_TRIANGLES, model.m_NumberOfIndices, GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, model.m_NumberOfVertices);
        }
    }

    void Shader::Draw(const std::vector<ModelComponent>& models) const
    {
        for (const auto& model : models) {
            Draw(model);
        }
    }

    void Shader::SetBool(const std::string& name, bool value) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform1i(uniLoc, static_cast<int>(value));
    }

    void Shader::SetInt(const std::string& name, int value) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform1i(uniLoc, value);
    }

    void Shader::SetFloat(const std::string& name, float value) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform1f(uniLoc, value);
    }

    void Shader::SetTexture(const std::string& name, unsigned int binding) const
    {
        Helper::RuntimeAssert(31 >= binding && binding >= 0, "Texture global state binding index must be in the range [0, 31].");
        SetInt(name, binding);
    }

    void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform2fv(uniLoc, 1, &value[0]);
    }
    void Shader::SetVec2(const std::string& name, float x, float y) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform2f(uniLoc, x, y);
    }
    void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform3fv(uniLoc, 1, &value[0]);
    }
    void Shader::SetVec3(const std::string& name, float x, float y, float z) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform3f(uniLoc, x, y, z);
    }
    void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform4fv(uniLoc, 1, &value[0]);
    }
    void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform4f(uniLoc, x, y, z, w);
    }
    void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniformMatrix2fv(uniLoc, 1, GL_FALSE, &mat[0][0]);
    }
    void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniformMatrix3fv(uniLoc, 1, GL_FALSE, &mat[0][0]);
    }
    void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUseProgram(m_ID);
        auto uniLoc = glGetUniformLocation(m_ID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniformMatrix4fv(uniLoc, 1, GL_FALSE, &mat[0][0]);        // or use glm::value_ptr(model)
    }

}