#pragma once
#include "Component.h"
#include <string>
#include <map>

namespace Charis {

	/// <summary>A model is a set of components (or just one) and can be created from model files or components.</summary>
	class Model
	{
	public:
		/// <summary>
		/// Constructor for a Model.
		/// A model constructed from a file will contain standardized vertex attributes which shaders must accomodate.
		/// For vertex shader input attributes, at locations 0-4, the following are expected: 
		/// vec3 position, vec3 normal, vec2 texture coordinate, vec3 tangent, vec3 bitangent.
		/// </summary>
		/// <param name="filepath">Path to model file to be loaded.</param>
		Model(const std::string& filepath);
		/// <summary>
		/// Constructor for a Model.
		/// </summary>
		/// <param name="components">A list of components, sharing the same local coordinate system, that together make up a model.</param>
		Model(const std::vector<Component>& components);

		/// <summary>
		/// If the model was constructed from a file then this function returns a map of loaded textures, 
		/// with file names as keys and their textures as values. 
		/// </summary>
		const std::map<std::string, Texture>& LoadedTextures() const { return m_LoadedTextures; }
		std::vector<Component> Components;
	private:
		std::map<std::string, Texture> m_LoadedTextures;
	};

}


