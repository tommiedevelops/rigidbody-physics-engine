#include "AssetManager.h"

#include <iostream>
#include <string>

namespace PhysicsEngine
{
	Mesh 
	Assets::ConvertToEngineMesh(const aiMesh* mesh, std::string meshName)
	{
		if (!mesh) throw std::logic_error("provided mesh was null");

		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;

		for (unsigned int i{ 0 }; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex{ };
			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z;

			if (mesh->mNormals)
			{
				vertex.normal.x = mesh->mNormals[i].x;
				vertex.normal.y = mesh->mNormals[i].y;
				vertex.normal.z = mesh->mNormals[i].z;
			}

			if (mesh->mTextureCoords[0])
			{
				vertex.uv.x = mesh->mTextureCoords[0][i].x;
				vertex.uv.y = mesh->mTextureCoords[0][i].y;
			}

			vertices.push_back(vertex);
		}

		for (unsigned int faceIdx{ 0 }; faceIdx < mesh->mNumFaces; ++faceIdx)
		{
			const auto& face = mesh->mFaces[faceIdx];

			for (unsigned int j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		return Mesh{ vertices, indices, meshName};
	}

	void
	Assets::AddMesh(
		std::string pathToMesh,
		std::string meshName
	)
	{
		/*
		This implementation does not support submeshes or indexed materials
		*/

		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(pathToMesh, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			throw std::logic_error("There was an error loading the model");
		}

		m_Meshes.push_back( ConvertToEngineMesh(scene->mMeshes[0], meshName) );
	}

	void Assets::AddTexture(
		std::string pathToTexture,
		std::string textureName
	)
	{
		m_Textures.push_back(Texture(pathToTexture, textureName));
	}

	void Assets::AddShader(
		std::string pathToVertexShader,
		std::string pathToFragmentShader,
		std::string shaderName
	)
	{
		m_Shaders.push_back(Shader(pathToVertexShader, pathToFragmentShader, shaderName));
	}

	Mesh* Assets::GetMesh(std::string meshName)
	{
		for (unsigned int i{ 0 }; i < m_Meshes.size(); ++i)
		{ 
			if (meshName == m_Meshes[i].GetName())
				return &m_Meshes[i];
		}

		return nullptr;
	}

	Texture* Assets::GetTexture(std::string textureName)
	{
		for (unsigned int i{ 0 }; i < m_Textures.size(); ++i)
		{
			if (textureName == m_Textures[i].GetName())
				return &m_Textures[i];
		}

		return nullptr;

	}

	Shader* Assets::GetShader(std::string shaderName)
	{
		for (unsigned int i{ 0 }; i < m_Shaders.size(); ++i)
		{
			if (shaderName == m_Shaders[i].GetName())
				return &m_Shaders[i];
		}

		return nullptr;

	}

	void Assets::CreateMaterial(std::string materialName, Shader* shader, Texture* texture)
	{
		m_Materials.push_back(Material(materialName, shader, texture));
	}


	Material* Assets::GetMaterial(std::string materialName)
	{
		for (unsigned int i{ 0 }; i < m_Materials.size(); ++i)
		{
			if (materialName == m_Shaders[i].GetName())
				return &m_Materials[i];
		}

		return nullptr;

	}

}