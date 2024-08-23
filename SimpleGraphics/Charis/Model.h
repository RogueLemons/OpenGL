#pragma once
#include <vector>
#include <array>

namespace Charis {

	using TriangleIndices = std::array<unsigned int, 3>;

	class Model
	{
	public:
		Model(const float* vertexAttributes, unsigned int numberOfVertices, const std::vector<unsigned int>& floatsPerAttributePerVertex);
		Model(const std::vector<float>& vertexAttributes, const std::vector<unsigned int>& floatsPerAttributePerVertex);
		Model(const float* vertexAttributes, unsigned int numberOfVertices, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& floatsPerAttributePerVertex);
		Model(const std::vector<float>& vertexAttributes, const std::vector<TriangleIndices>& indexTriangles, const std::vector<unsigned int>& floatsPerAttributePerVertex);
		~Model();

		friend class SimpleShader;
		friend class Shader;

	private:
		unsigned int m_VAO;
		unsigned int m_NumberOfVertices;
		unsigned int m_VBO;
		
		bool m_UsingIBO;
		unsigned int m_NumberOfIndices;
		unsigned int m_IBO;
	};

	/*template<class V>
	Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& floatsPerAttributePerVertex);
	template<class V>
	Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& floatsPerAttributePerVertex);*/
}

