#pragma once
#include "Component.h"
#include <string>
#include <map>

namespace Charis {

	class Model
	{
	public:
		Model(const std::string& filepath);
		Model(const std::vector<Component>& components);

		const std::map<std::string, Texture>& LoadedTextures() const { return m_LoadedTextures; }
		std::vector<Component> Components;
	private:
		std::map<std::string, Texture> m_LoadedTextures;
	};

}


