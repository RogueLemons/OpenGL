#include "Model.h"
#include "Utility.h"
#include <numeric>

// Libraries
#include <glad/glad.h>

struct VertexInfo { unsigned int VAO; unsigned int VBO; unsigned int numberOfVertices; };
static VertexInfo SetAttributesAndVertices(const float* vertices, unsigned int numberOfVertices, const std::vector<unsigned int>& floatsPerAttribute) 
{
	VertexInfo vertInfo{};
	vertInfo.numberOfVertices = numberOfVertices;

	// Set up vertex attributes
	glGenVertexArrays(1, &vertInfo.VAO);
	glBindVertexArray(vertInfo.VAO);
	const auto stride = sizeof(float) * std::reduce(floatsPerAttribute.begin(), floatsPerAttribute.end());
	int offset = 0;
	int attribute = 0;
	for (auto floatsInAttribute : floatsPerAttribute) {
		glVertexAttribPointer(attribute, floatsInAttribute, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(attribute);
		offset += floatsInAttribute;
		attribute++;
	}

	//Set up vertex buffer
	glGenBuffers(1, &vertInfo.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertInfo.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertices, vertices, GL_STATIC_DRAW);

	return vertInfo;
}

namespace Charis {

	Model::Model(const float* vertices, unsigned int numberOfVertices, const std::vector<unsigned int>& floatsPerAttribute)
	{
		Helper::RuntimeAssert(!floatsPerAttribute.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfVertices >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfVertices % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffers
		auto vertInfo = SetAttributesAndVertices(vertices, numberOfVertices, floatsPerAttribute);
		m_VAO = vertInfo.VAO;
		m_NumberOfVertices = vertInfo.numberOfVertices;
		m_VBO = vertInfo.VBO;

		// Set up index/element buffer
		m_UsingIBO = false;
		m_NumberOfIndices = 0;
		m_IBO = -1;
	}
	Model::Model(const std::vector<float>& vertices, const std::vector<unsigned int>& floatsPerAttribute) 
		: Model(vertices.data(), vertices.size(), floatsPerAttribute)
	{}

	Model::Model(const float* vertices, unsigned int numberOfVertices, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& floatsPerAttribute)
	{
		Helper::RuntimeAssert(!floatsPerAttribute.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfIndices >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfIndices % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffer
		auto vertInfo = SetAttributesAndVertices(vertices, numberOfVertices, floatsPerAttribute);
		m_VAO = vertInfo.VAO;
		m_NumberOfVertices = vertInfo.numberOfVertices;
		m_VBO = vertInfo.VBO;

		// Set up index/element buffer
		m_UsingIBO = true;
		m_NumberOfIndices = numberOfIndices;
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numberOfIndices, indices, GL_STATIC_DRAW);

	}

	Model::Model(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& floatsPerAttribute)
		: Model(vertices.data(), vertices.size(), indices.data(), indices.size(), floatsPerAttribute)
	{}

	Model::~Model()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);

		if (m_UsingIBO) 
			glDeleteBuffers(1, &m_IBO);
	}

	template<class V>
	Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& floatsPerAttribute) 
	{
		const auto floatsPerVertex = std::reduce(floatsPerAttribute.begin(), floatsPerAttribute.end());
		Helper::RuntimeAssert(sizeof(V) == sizeof(float) * floatsPerVertex, "Number of floats in simple vertex struct must match number of attribute floats.");
		return Model(vertices.data(), vertices.size(), floatsPerAttribute);
	}

	template<class V>
	Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& floatsPerAttribute)
	{
		const auto floatsPerVertex = std::reduce(floatsPerAttribute.begin(), floatsPerAttribute.end());
		Helper::RuntimeAssert(sizeof(V) == sizeof(float) * floatsPerVertex, "Number of floats in simple vertex struct must match number of attribute floats.");
		return Model(vertices.data(), vertices.size(), indices.data(), indices.size(), floatsPerAttribute);
	}

}