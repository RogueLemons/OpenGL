#pragma once
#include "Component.h"
#include <string>

namespace Charis {

	class Model
	{
	public:
		Model(const std::string& filepath);
		Model(const std::vector<Component>& components);

		std::vector<Component> Components;
	private:
	};

}


