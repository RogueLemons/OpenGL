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
		// SimpleShader(const char* vertexShader, const char* fragmentShader, InputType = Filepath);
		~SimpleShader();

		void Draw(const Model& model);
		void Draw(const std::vector<Model>& models);

	private:
		unsigned int ID;
	};

}