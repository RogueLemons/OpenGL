#pragma once
#include "ModelComponent.h"
#include <string>
#include <vector>

// Libraries
#include <glm/glm.hpp>

namespace Charis {

	/// <summary>An easy to use shader with GLM support. Contains methods to draw models and set shader uniform variables.</summary>
	class Shader
	{
	public:
		enum InputType {
			// Provides paths to files with shader code to constructor.
			Filepath,
			// Shader source code is provided directly as a string to constructor.
			InCode
		};
		/// <summary>
		/// Constructor for a shader class.
		/// </summary>
		/// <param name="vertexShader">Contains either the path to a file with vertex shader source code or the source code directly.</param>
		/// <param name="fragmentShader">Contains either the path to a file with fragment shader source code or the source code directly.</param>
		/// <param name="inputType">Decides if arguments are treated as file paths or source code. Default as file path.</param>
		Shader(const std::string& vertexShader, const std::string& fragmentShader, InputType inputType = Filepath);
		~Shader();

		// TODO: Reintroduce copy constructor and assignment operator
		Shader(const Shader&) = delete;
		Shader& operator =(const Shader&) = delete;

		// Uses this shader to draw a model.
		void Draw(const ModelComponent& model) const;
		// Uses this shader to draw a list of models.
		void Draw(const std::vector<ModelComponent>& models) const;

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetTexture(const std::string& name, unsigned int binding) const;

		void SetVec2(const std::string& name, const glm::vec2& value) const;
		void SetVec2(const std::string& name, float x, float y) const;
		void SetVec3(const std::string& name, const glm::vec3& value) const;
		void SetVec3(const std::string& name, float x, float y, float z) const;
		void SetVec4(const std::string& name, const glm::vec4& value) const;
		void SetVec4(const std::string& name, float x, float y, float z, float w) const;
		void SetMat2(const std::string& name, const glm::mat2& mat) const;
		void SetMat3(const std::string& name, const glm::mat3& mat) const;
		void SetMat4(const std::string& name, const glm::mat4& mat) const;


	private:
		unsigned int m_ID;
	};

}