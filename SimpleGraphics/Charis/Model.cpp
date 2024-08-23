#include "Model.h"
#include "Utility.h"
#include <numeric>

// Libraries
#include <glad/glad.h>

static unsigned int sum(const std::vector<unsigned int>& numbers) {
	return std::reduce(numbers.begin(), numbers.end());
}

struct VertexInfo { unsigned int VAO; unsigned int VBO; unsigned int numberOfVertices; };
static VertexInfo SetAttributesAndVertices(const float* vertexAttributes, unsigned int numberOfVertices, const std::vector<unsigned int>& floatsPerAttributePerVertex) 
{
	VertexInfo vertInfo{};
	vertInfo.numberOfVertices = numberOfVertices;

	// Set up vertex attributes
	glGenVertexArrays(1, &vertInfo.VAO);
	glBindVertexArray(vertInfo.VAO);
	const auto stride = sizeof(float) * sum(floatsPerAttributePerVertex);
	int offset = 0;
	int attribute = 0;
	for (auto floatsPerAttribute : floatsPerAttributePerVertex) {
		glVertexAttribPointer(attribute, floatsPerAttribute, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(attribute);
		offset += floatsPerAttribute;
		attribute++;
	}

	//Set up vertex buffer
	glGenBuffers(1, &vertInfo.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertInfo.VBO);
	glBufferData(GL_ARRAY_BUFFER, stride * numberOfVertices, vertexAttributes, GL_STATIC_DRAW);

	return vertInfo;
}

namespace Charis {

	Model::Model(const float* vertexAttributes, unsigned int numberOfVertices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
	{
		Helper::RuntimeAssert(!floatsPerAttributePerVertex.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfVertices >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfVertices % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffers
		auto vertInfo = SetAttributesAndVertices(vertexAttributes, numberOfVertices, floatsPerAttributePerVertex);
		m_VAO = vertInfo.VAO;
		m_NumberOfVertices = vertInfo.numberOfVertices;
		m_VBO = vertInfo.VBO;

		// Set up index/element buffer
		m_UsingIBO = false;
		m_NumberOfIndices = 0;
		m_IBO = -1;
	}
	Model::Model(const std::vector<float>& vertexAttributes, const std::vector<unsigned int>& floatsPerAttributePerVertex) 
		: Model(vertexAttributes.data(), vertexAttributes.size() / sum(floatsPerAttributePerVertex), floatsPerAttributePerVertex)
	{}

	Model::Model(const float* vertexAttributes, unsigned int numberOfVertices, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
	{
		Helper::RuntimeAssert(!floatsPerAttributePerVertex.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfIndices >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfIndices % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffer
		auto vertInfo = SetAttributesAndVertices(vertexAttributes, numberOfVertices, floatsPerAttributePerVertex);
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

	Model::Model(const std::vector<float>& vertexAttributes, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
		: Model(vertexAttributes.data(), vertexAttributes.size(), indices.data(), indices.size(), floatsPerAttributePerVertex)
	{}

	Model::~Model()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);

		if (m_UsingIBO) 
			glDeleteBuffers(1, &m_IBO);
	}

	template<class V>
	Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& floatsPerAttributePerVertex) 
	{
		const auto floatsPerVertex = sum(floatsPerAttributePerVertex);
		Helper::RuntimeAssert(sizeof(V) == sizeof(float) * floatsPerVertex, "Number of floats in simple vertex struct must match number of attribute floats.");
		return Model(vertices.data(), vertices.size(), floatsPerAttributePerVertex);
	}

	template<class V>
	Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
	{
		const auto floatsPerVertex = sum(floatsPerAttributePerVertex);
		Helper::RuntimeAssert(sizeof(V) == sizeof(float) * floatsPerVertex, "Number of floats in simple vertex struct must match number of attribute floats.");
		return Model(vertices.data(), vertices.size(), indices.data(), indices.size(), floatsPerAttributePerVertex);
	}

}