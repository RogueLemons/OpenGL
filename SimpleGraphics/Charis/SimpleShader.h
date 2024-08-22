#pragma once
#include "Model.h"
#include <string>
#include <vector>

namespace Charis {

	/// <summary>An easy to use shader that does not have any requirements to use.</summary>
	class SimpleShader
	{
	public:
		enum InputType {
			// Provides paths to files with shader code to constructor.
			Filepath,
			// Shader source code is provided directly as a string to constructor.
			InCode
		};
		SimpleShader(const std::string& vertexShader, const std::string& fragmentShader, InputType inputType = Filepath);
		~SimpleShader();

		void Draw(const Model& model) const;
		void Draw(const std::vector<Model>& models) const;

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

	private:
		unsigned int mID;
	};

}