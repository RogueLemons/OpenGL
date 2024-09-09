#include "Model.h"
#include "Texture.h"
#include <iostream>

// Libraries
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace {
    using namespace Charis;

	std::string Directory;

    const std::vector<unsigned int> FloatsPerAttribute = { 3, 3, 2, 3, 3 };
    constexpr unsigned int TotalFloats = 14;
	struct VertexAttributes {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;

        //bone indexes which will influence this vertex
        // int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        // float m_Weights[MAX_BONE_INFLUENCE];
	};

    struct ModelMemberRefs {
        std::vector<Component>& components;
        std::map<std::string, Texture>& loadedTextures;
    };
	void LoadModel(const std::string& filepath, ModelMemberRefs& mmr);
	void ProcessNode(aiNode* node, const aiScene* scene, ModelMemberRefs& mmr);
	Component ProcessMesh(aiMesh* mesh, const aiScene* scene, ModelMemberRefs& mmr);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::TextureType textureType, ModelMemberRefs& mmr);
    Component CreateModelComponentFromVertexAttributes(const std::vector<VertexAttributes>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);

	void LoadModel(const std::string& filepath, ModelMemberRefs& mmr)
	{
		// read file via ASSIMP
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}
		// retrieve the directory path of the filepath
		Directory = filepath.substr(0, filepath.find_last_of('/'));

		// process ASSIMP's root node recursively
		ProcessNode(scene->mRootNode, scene, mmr);
	}

    void ProcessNode(aiNode* node, const aiScene* scene, ModelMemberRefs& mmr)
    {
        // process each mesh located at the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene. 
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            mmr.components.push_back(ProcessMesh(mesh, scene, mmr));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene, mmr);
        }
    }

	Component ProcessMesh(aiMesh* mesh, const aiScene* scene, ModelMemberRefs& mmr)
	{
        static_assert(sizeof(VertexAttributes) == TotalFloats * sizeof(float));

        // data to fill
        std::vector<VertexAttributes> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            VertexAttributes vertex{};
            glm::vec3 vec{}; // declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vec.x = mesh->mVertices[i].x;
            vec.y = mesh->mVertices[i].y;
            vec.z = mesh->mVertices[i].z;
            vertex.Position = vec;
            // normals
            if (mesh->HasNormals())
            {
                vec.x = mesh->mNormals[i].x;
                vec.y = mesh->mNormals[i].y;
                vec.z = mesh->mNormals[i].z;
                vertex.Normal = vec;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = glm::vec2(vec);
            }
            if (mesh->HasTangentsAndBitangents()) {
                // tangent
                vec.x = mesh->mTangents[i].x;
                vec.y = mesh->mTangents[i].y;
                vec.z = mesh->mTangents[i].z;
                vertex.Tangent = vec;
                // bitangent
                vec.x = mesh->mBitangents[i].x;
                vec.y = mesh->mBitangents[i].y;
                vec.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vec;
            }

            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, Texture::Diffuse, mmr);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, Texture::Specular, mmr);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, Texture::Normal, mmr);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, Texture::Height, mmr);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        // 5. ambient maps
        std::vector<Texture> ambientMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, Texture::Ambient, mmr);
        textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());

        // return a component object created from the extracted mesh data
        return CreateModelComponentFromVertexAttributes(vertices, indices, textures);
	}

    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::TextureType textureType, ModelMemberRefs& mmr)
    {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            // Get texture filename
            aiString aiFilename;
            mat->GetTexture(type, i, &aiFilename);
            std::string filename = aiFilename.C_Str();

            // Check if texture has already been loaded, otherwise load it
            if (mmr.loadedTextures.contains(filename)) {
                auto& texture = mmr.loadedTextures.at(filename);
                textures.push_back(texture);
            }
            else {
                auto texture = Texture(Directory + '/' + filename, textureType);
                textures.push_back(texture);
                mmr.loadedTextures.insert({ filename, texture });
            }

        }
        return textures;
    }

    Component CreateModelComponentFromVertexAttributes(const std::vector<VertexAttributes>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
    {
        static_assert(sizeof(VertexAttributes) == sizeof(float) * TotalFloats, "Number of floats in simple VertexAttributes struct must match number of attribute floats.");

        auto vertexArray = reinterpret_cast<const float*>(vertices.data());
        auto vertexCount = static_cast<unsigned int>(TotalFloats * vertices.size());
        auto indexArray = indices.data();
        auto indexCount = static_cast<unsigned int>(indices.size());

        auto component = Component(vertexArray, vertexCount, indexArray, indexCount, FloatsPerAttribute);
        component.Textures = textures;
        return component;
    }



}


namespace Charis {

	Model::Model(const std::string& filepath)
	{
        ModelMemberRefs mmr = { .components = Components, .loadedTextures = m_LoadedTextures };
        LoadModel(filepath, mmr);
	}

	Model::Model(const std::vector<Component>& components)
		: Components(components)
	{}

}

