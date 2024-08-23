#pragma once
#include <vector>

namespace Charis {

	class Model
	{
	public:
		Model(const float* vertices, unsigned int numberOfVertices, const std::vector<unsigned int>& floatsPerAttribute);
		Model(const std::vector<float>& vertices, const std::vector<unsigned int>& floatsPerAttribute);
		Model(const float* vertices, unsigned int numberOfVertices, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& floatsPerAttribute);
		Model(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& floatsPerAttribute);
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

	template<class V>
	static Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& floatsPerAttribute);
	template<class V>
	static Model CreateModelFromStructs(const std::vector<V>& vertices, const std::vector<unsigned int>& indices, const std::vector<unsigned int>& floatsPerAttribute);
}

