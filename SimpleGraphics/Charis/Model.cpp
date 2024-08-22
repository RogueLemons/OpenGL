#include "Model.h"
#include "Utility.h"
#include <numeric>

// Libraries
#include <glad/glad.h>

struct Buffers { unsigned int VAO; unsigned int VBO; unsigned int numberOfVertices; };
static Buffers SetAttributesAndVertices(const float* vertices, unsigned int numberOfVertices, const std::vector<unsigned int>& attributeFloatSizes) 
{
	Buffers buffers{};
	buffers.numberOfVertices = numberOfVertices;

	// Set up vertex attributes
	glGenVertexArrays(1, &buffers.VAO);
	glBindVertexArray(buffers.VAO);
	const auto stride = sizeof(float) * std::reduce(attributeFloatSizes.begin(), attributeFloatSizes.end());
	int offset = 0;
	int attribute = 0;
	for (auto attributeFloatSize : attributeFloatSizes) {
		glVertexAttribPointer(attribute, attributeFloatSize, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(attribute);
		offset += attributeFloatSize;
		attribute++;
	}

	//Set up vertex buffer
	glGenBuffers(1, &buffers.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertices, vertices, GL_STATIC_DRAW);

	return buffers;
}

namespace Charis {

	Model::Model(const float* vertices, unsigned int numberOfVertices, const std::vector<unsigned int>& attributeFloatSizes)
	{
		Helper::RuntimeAssert(!attributeFloatSizes.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfVertices >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfVertices % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffers
		auto buffers = SetAttributesAndVertices(vertices, numberOfVertices, attributeFloatSizes);
		mVAO = buffers.VAO;
		mNumberOfVertices = buffers.numberOfVertices;
		mVBO = buffers.VBO;

		// Set up index/element buffer
		mUsingIBO = false;
		mNumberOfIndices = 0;
		mIBO = -1;
	}
	Model::Model(const std::vector<float>& vertices, const std::vector<unsigned int>& attributeFloatSizes) 
		: Model(vertices.data(), vertices.size(), attributeFloatSizes)
	{}

	Model::Model(const float* vertices, unsigned int numberOfVertices, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& attributeFloatSizes)
	{
		Helper::RuntimeAssert(!attributeFloatSizes.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfVertices >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfVertices % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffers
		auto buffers = SetAttributesAndVertices(vertices, numberOfVertices, attributeFloatSizes);
		mVAO = buffers.VAO;
		mNumberOfVertices = buffers.numberOfVertices;
		mVBO = buffers.VBO;

		// Set up index/element buffer
		mUsingIBO = true;
		glGenBuffers(1, &mIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numberOfIndices, indices, GL_STATIC_DRAW);
		mNumberOfIndices = numberOfIndices;

	}

	Model::Model(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& attributeFloatSizes)
		: Model(vertices.data(), vertices.size(), indices.data(), indices.size(), attributeFloatSizes)
	{}

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