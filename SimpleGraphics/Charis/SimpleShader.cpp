#include "SimpleShader.h"
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

	SimpleShader::SimpleShader(const std::string& vertexShader, const std::string& fragmentShader, InputType inputType)
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

        mID = glCreateProgram();
        glAttachShader(mID, vertex);
        glAttachShader(mID, fragment);
        glLinkProgram(mID);
        CheckCompileErrors(mID, ShaderType::Program);

        // 3. delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
	}

	SimpleShader::~SimpleShader()
	{
		glDeleteProgram(mID);
	}

    void SimpleShader::Draw(const Model& model) const
    {
        glUseProgram(mID);
        glBindBuffer(GL_ARRAY_BUFFER, model.mVBO);
        glBindVertexArray(model.mVAO);

        if (model.mUsingIBO) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.mIBO);
            glDrawElements(GL_TRIANGLES, model.mNnumberOfIndices, GL_UNSIGNED_INT, 0);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, model.mNumberOfVertices);
        }
    }

    void SimpleShader::Draw(const std::vector<Model>& models) const
    {
        for (const auto& model : models) {
            Draw(model);
        }
    }

    void SimpleShader::setBool(const std::string& name, bool value) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform1i(uniLoc, static_cast<int>(value));
    }

    void SimpleShader::setInt(const std::string& name, int value) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform1i(uniLoc, value);
    }

    void SimpleShader::setFloat(const std::string& name, float value) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform1f(uniLoc, value);
    }

}