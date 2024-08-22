#pragma once
#include "Model.h"
#include <string>
#include <vector>

namespace Charis {

	/// <summary>An easy to use shader that does not have any requirements to use. Contains methods to draw models and set shader uniform variables.</summary>
	class SimpleShader
	{
	public:
		enum InputType {
			// Provides paths to files with shader code to constructor.
			Filepath,
			// Shader source code is provided directly as a string to constructor.
			InCode
		};
		/// <summary>
		/// Constructor for a simple shader class.
		/// </summary>
		/// <param name="vertexShader">Contains either the path to a file with vertex shader source code or the source code directly.</param>
		/// <param name="fragmentShader">Contains either the path to a file with fragment shader source code or the source code directly.</param>
		/// <param name="inputType">Decides if arguments are treated as file paths or source code. Default as file path.</param>
		SimpleShader(const std::string& vertexShader, const std::string& fragmentShader, InputType inputType = Filepath);
		~SimpleShader();

		// Uses this shader to draw a model.
		void Draw(const Model& model) const;
		// Uses this shader to draw a list of models.
		void Draw(const std::vector<Model>& models) const;

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;

	protected:
		unsigned int mID;
	};

}