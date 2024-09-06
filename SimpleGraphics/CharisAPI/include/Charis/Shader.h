#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include <memory>

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
		/// <param name="numberOfDrawableTextures">
		/// Number of textures, per texture type, that will automatically be bound and used when drawing with this texture. 
		/// For example, with a limit at 3, the shader is expected to support 3 diffuse textures, 3 specular textures, and so on.
		/// The naming convention follows {TextureType}Texture_{i}. For example, the 3rd diffuse texture is named DiffuseTexture_3.
		/// When drawing the texture bindings start at 31 and counts downwards, meaning for a limit at 3 bindings 0 to 19 
		/// are safe to use for textures not bound to the model component. A limit at 0 means all texture binding management
		/// must be manual.
		/// </param>
		Shader(const std::string& vertexShader, const std::string& fragmentShader, InputType inputType = Filepath, unsigned int numberOfDrawableTextures = 0);
		~Shader();

		// Uses this shader to draw a model.
		void Draw(const Component& modelComponent) const;
		// Uses this shader to draw a list of models.
		void Draw(const std::vector<Component>& modelComponents) const;

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
		struct ShaderMember {
			unsigned int ID{};
			unsigned int NumberOfDrawableTextures{};
		};
		std::shared_ptr<ShaderMember> m = std::make_shared<ShaderMember>();
	};

}