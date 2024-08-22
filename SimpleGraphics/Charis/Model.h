#pragma once
#include <vector>

namespace Charis {

	class Model
	{
	public:
		Model(const float* vertices, unsigned int numberOfVertices, const std::vector<unsigned int>& attributeFloatSizes);
		Model(const std::vector<float>& vertices, const std::vector<unsigned int>& attributeFloatSizes);
		Model(const float* vertices, unsigned int numberOfVertices, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& attributeFloatSizes);
		Model(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& attributeFloatSizes);
		~Model();

		friend class SimpleShader;
		friend class Shader;

	private:
		unsigned int mVAO;
		unsigned int mNumberOfVertices;
		unsigned int mVBO;
		
		bool mUsingIBO;
		unsigned int mNnumberOfIndices;
		unsigned int mIBO;
	};

	template<class V>
	static Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& attributeFloatSizes);
	template<class V>
	static Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& attributeFloatSizes);
}

