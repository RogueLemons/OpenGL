#include "ModelComponent.h"
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

	ModelComponent::ModelComponent(const float* vertexAttributes, unsigned int numberOfVertexAttributes, const std::vector<unsigned int>& floatsPerAttributePerVertex)
	{
		Helper::RuntimeAssert(!floatsPerAttributePerVertex.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfVertexAttributes >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfVertexAttributes % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffers
		auto vertInfo = SetAttributesAndVertices(vertexAttributes, numberOfVertexAttributes, floatsPerAttributePerVertex);
		m->VAO = vertInfo.VAO;
		m->NumberOfVertices = vertInfo.numberOfVertices;
		m->VBO = vertInfo.VBO;

		// Set up index/element buffer
		m->UsingIBO = false;
		m->NumberOfIndices = 0;
		m->IBO = -1;
	}
	ModelComponent::ModelComponent(const std::vector<float>& vertexAttributes, const std::vector<unsigned int>& floatsPerAttributePerVertex) 
		: ModelComponent(vertexAttributes.data(), vertexAttributes.size(), floatsPerAttributePerVertex)
	{}

	ModelComponent::ModelComponent(const float* vertexAttributes, unsigned int numberOfVertexAttributes, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& floatsPerAttributePerVertex)
	{
		Helper::RuntimeAssert(!floatsPerAttributePerVertex.empty(), "Must provide attribute float sizes.");
		Helper::RuntimeAssert(numberOfIndices >= 3, "Must provide at least 3 vertices to model.");
		Helper::RuntimeAssert(numberOfIndices % 3 == 0, "Number of vertices must be multiple of 3.");

		// Set attributes and vertex buffer
		auto vertInfo = SetAttributesAndVertices(vertexAttributes, numberOfVertexAttributes, floatsPerAttributePerVertex);
		m->VAO = vertInfo.VAO;
		m->NumberOfVertices = vertInfo.numberOfVertices;
		m->VBO = vertInfo.VBO;

		// Set up index/element buffer
		m->UsingIBO = true;
		m->NumberOfIndices = numberOfIndices;
		glGenBuffers(1, &m->IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * numberOfIndices, indices, GL_STATIC_DRAW);

	}

	ModelComponent::ModelComponent(const std::vector<float>& vertexAttributes, const std::vector<TriangleIndices>& indexTriangles, const std::vector<unsigned int>& floatsPerAttributePerVertex)
		: ModelComponent(vertexAttributes.data(), vertexAttributes.size(), reinterpret_cast<const unsigned int*>(indexTriangles.data()), 3 * indexTriangles.size(), floatsPerAttributePerVertex)
	{
		static_assert(sizeof(TriangleIndices) == 3 * sizeof(float));
	}

	ModelComponent::~ModelComponent()
	{
		if (m.use_count() > 1)
			return;

		glDeleteVertexArrays(1, &m->VAO);
		glDeleteBuffers(1, &m->VBO);

		if (m->UsingIBO) 
			glDeleteBuffers(1, &m->IBO);
	}

}