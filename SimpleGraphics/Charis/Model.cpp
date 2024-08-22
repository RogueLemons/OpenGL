#include "Model.h"

// Libraries
#include <glad/glad.h>

namespace Charis {

	Model::Model(const float* vertices, unsigned int numberOfVertices, const std::vector<unsigned int>& attributeFloatSizes)
	{
	}
	Model::Model(const std::vector<float>& vertices, const std::vector<unsigned int>& attributeFloatSizes) 
	{
	}

	Model::Model(const float* vertices, unsigned int numberOfVertices, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& attributeFloatSizes)
	{
	}

	Model::Model(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& attributeFloatSizes)
	{
	}

	Model::~Model()
	{
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);

		if (mUsingIBO) 
			glDeleteBuffers(1, &mIBO);
	}

	template<class V>
	Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& attributeFloatSizes) 
	{
		return Model();
	}

	template<class V>
	Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& attributeFloatSizes, const std::vector<unsigned int>& indices)
	{
		return Model();
	}

}