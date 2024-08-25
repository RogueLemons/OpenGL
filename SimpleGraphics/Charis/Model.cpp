#include "Model.h"
#include "Utility.h"
#include <numeric>

// Libraries
#include <glad/glad.h>

static unsigned int sum(const std::vector<unsigned int>& numbers) {
	return std::reduce(numbers.begin(), numbers.end());
}

struct VertexInfo { unsigned int VAO; unsigned int VBO; unsigned int numberOfVertices; };
static VertexInfo SetAttributesAndVertices(const float* vertexAttributes, unsigned int numberOfVertexAttributes, const std::vector<unsigned int>& floatsPerAttributePerVertex) 
{
	VertexInfo vertInfo{};
	vertInfo.numberOfVertices = numberOfVertexAttributes;

	// Create and bind vertex attribute object
	glGenVertexArrays(1, &vertInfo.VAO);
	glBindVertexArray(vertInfo.VAO);
	
	//Create and set vertex buffer object
	glGenBuffers(1, &vertInfo.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertInfo.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfVertexAttributes, vertexAttributes, GL_STATIC_DRAW);
	
	// Set vertex attributes
	int offset = 0;
	int attribute = 0;
	for (auto floatsInAttribute : floatsPerAttributePerVertex) {
		const auto stride = sizeof(float) * sum(floatsPerAttributePerVertex);
		glVertexAttribPointer(attribute, floatsInAttribute, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(attribute);
		offset += floatsInAttribute;
		attribute++;
	}

	return vertInfo;
}

namespace Charis {

	Model::Model(const float* vertexAttributes, unsigned int numberOfVertexAttributes, const std::vector<unsigned int>& floatsPerAttributePerVertex)
	{
		Helper::RuntimeAssert(!floatsPerAttributePerVertex.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfVertexAttributes >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfVertexAttributes % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffers
		auto vertInfo = SetAttributesAndVertices(vertexAttributes, numberOfVertexAttributes, floatsPerAttributePerVertex);
		m_VAO = vertInfo.VAO;
		m_NumberOfVertices = vertInfo.numberOfVertices;
		m_VBO = vertInfo.VBO;

		// Set up index/element buffer
		m_UsingIBO = false;
		m_NumberOfIndices = 0;
		m_IBO = -1;
	}
	Model::Model(const std::vector<float>& vertexAttributes, const std::vector<unsigned int>& floatsPerAttributePerVertex) 
		: Model(vertexAttributes.data(), vertexAttributes.size(), floatsPerAttributePerVertex)
	{}

	Model::Model(const float* vertexAttributes, unsigned int numberOfVertexAttributes, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
	{
		Helper::RuntimeAssert(!floatsPerAttributePerVertex.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfIndices >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfIndices % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffer
		auto vertInfo = SetAttributesAndVertices(vertexAttributes, numberOfVertexAttributes, floatsPerAttributePerVertex);
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

	Model::Model(const std::vector<float>& vertexAttributes, const std::vector<TriangleIndices>& indexTriangles, const std::vector<unsigned int>& floatsPerAttributePerVertex)
		: Model(vertexAttributes.data(), vertexAttributes.size(), reinterpret_cast<const unsigned int*>(indexTriangles.data()), 3 * indexTriangles.size(), floatsPerAttributePerVertex)
	{
		static_assert(sizeof(TriangleIndices) == 3 * sizeof(float));
	}

	Model::~Model()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);

		if (m_UsingIBO) 
			glDeleteBuffers(1, &m_IBO);
	}

}