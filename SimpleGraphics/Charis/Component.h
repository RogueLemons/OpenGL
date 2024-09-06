#pragma once
#include "Texture.h"
#include <vector>
#include <array>
#include <memory>

namespace Charis {

	/// <summary>Contains vertex indices to make up a triangle.</summary>
	using TriangleIndices = std::array<unsigned int, 3>;

	/// <summary>
	/// A model contains vertices and the necessary information to be able to draw it to the screen.
	/// This can for instance be a triangle or a cube.
	/// </summary>
	class Component
	{
	public:
		/// <summary>Constructor for a model Component.</summary>
		/// <param name="vertexAttributes">Pointer to an array that contains all vertices and vertex attributes.</param>
		/// <param name="numberOfVertices">Number of vertex attributes in the array.</param>
		/// <param name="floatsPerAttributePerVertex">This provides a list that for each shader attribute provides the number of floats it contains. 
		/// For example, if the shaders first input is vec3 xyz and second input is vec3 rgb, then this argument should be { 3, 3 }.</param>
		Component(const float* vertexAttributes, unsigned int numberOfVertexAttributes, const std::vector<unsigned int>& floatsPerAttributePerVertex);
		/// <summary>Constructor for a model Component.</summary>
		/// <param name="vertexAttributes">Vector that contains all vertices and relevant vertex attributes.</param>
		/// <param name="floatsPerAttributePerVertex">This provides a list that for each shader attribute provides the number of floats it contains. 
		/// For example, if the shaders first input is vec3 xyz and second input is vec3 rgb, then this argument should be { 3, 3 }.</param>
		Component(const std::vector<float>& vertexAttributes, const std::vector<unsigned int>& floatsPerAttributePerVertex);
		/// <summary>Constructor for a model Component.</summary>
		/// <param name="vertexAttributes">Pointer to an array that contains all vertices and vertex attributes.</param>
		/// <param name="numberOfVertexAttributes">Number of vertex attributes in the array.</param>
		/// <param name="indices">Pointer to an array containing indices to vertices, where every three indices make up a triangle.</param>
		/// <param name="numberOfIndices">Number of indices in the array.</param>
		/// <param name="floatsPerAttributePerVertex">This provides a list that for each shader attribute provides the number of floats it contains. 
		/// For example, if the shaders first input is vec3 xyz and second input is vec3 rgb, then this argument should be { 3, 3 }.</param>
		Component(const float* vertexAttributes, unsigned int numberOfVertexAttributes, const unsigned int* indices, unsigned int numberOfIndices, const std::vector<unsigned int>& floatsPerAttributePerVertex);
		/// <summary>Constructor for a model Component.</summary>
		/// <param name="vertexAttributes">Vector that contains all vertices and relevant vertex attributes.</param>
		/// <param name="indexTriangles">Vector containing vertex indices in sets of three that each form a triangle.</param>
		/// <param name="floatsPerAttributePerVertex">This provides a list that for each shader attribute provides the number of floats it contains. 
		/// For example, if the shaders first input is vec3 xyz and second input is vec3 rgb, then this argument should be { 3, 3 }.</param>
		Component(const std::vector<float>& vertexAttributes, const std::vector<TriangleIndices>& indexTriangles, const std::vector<unsigned int>& floatsPerAttributePerVertex);
		
		~Component();
		
		// List of textures related to this model component.
		std::vector<Texture> Textures;

		friend class Shader;
	private:
		struct ModelComponentMember {
			unsigned int VAO{};
			unsigned int NumberOfVertices{};
			unsigned int VBO{};
		
			bool UsingIBO{};
			unsigned int NumberOfIndices{};
			unsigned int IBO{};
		};
		std::shared_ptr<ModelComponentMember> m = std::make_shared<ModelComponentMember>();

	};

}

