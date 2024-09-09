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

		std::vector<Component> Components;
	private:
		std::map<std::string, Texture> m_LoadedTextures;
	};

}


