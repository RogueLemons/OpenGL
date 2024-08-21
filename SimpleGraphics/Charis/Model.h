#pragma once
#include <vector>

namespace Charis {

	class Model
	{
	public:
		Model(const float* vertices, unsigned int size, unsigned int stride, const std::vector<unsigned int>& attributeFloatSizes);
		Model(const std::vector<float>& vertices, unsigned int stride, const std::vector<unsigned int>& attributeFloatSizes);
		~Model();

		friend class SimpleShader;
		friend class Shader;

	private:
		unsigned int VBO;
		unsigned int VAO;
		unsigned int numberOfVertices;
	};

	template<class V>
	static Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& attributeFloatSizes);
}

