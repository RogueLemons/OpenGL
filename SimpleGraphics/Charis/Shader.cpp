#include "Shader.h"
#include "Utility.h"

// Libraries
#include <glad/glad.h>

namespace Charis {

    void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform2fv(uniLoc, 1, &value[0]);
    }
    void Shader::SetVec2(const std::string& name, float x, float y) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform2f(uniLoc, x, y);
    }
    void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform3fv(uniLoc, 1, &value[0]);
    }
    void Shader::SetVec3(const std::string& name, float x, float y, float z) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform3f(uniLoc, x, y, z);
    }
    void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform4fv(uniLoc, 1, &value[0]);
    }
    void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniform4f(uniLoc, x, y, z, w);
    }
    void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniformMatrix2fv(uniLoc, 1, GL_FALSE, &mat[0][0]);
    }
    void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniformMatrix3fv(uniLoc, 1, GL_FALSE, &mat[0][0]);
    }
    void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
    {
        auto uniLoc = glGetUniformLocation(mID, name.c_str());
        Helper::RuntimeAssert(uniLoc != -1, "Shader uniform does not exist.");
        glUniformMatrix4fv(uniLoc, 1, GL_FALSE, &mat[0][0]);        // or use glm::value_ptr(model)
    }

}