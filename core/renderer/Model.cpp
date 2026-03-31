#include "Model.h"
#include "Texture.h"

#include <iostream>

namespace PhysicsEngine
{
	static std::vector<Texture> g_Textures; // global to this file

	AssimpModel::AssimpModel(std::string path)
	{
		loadModel(path);
	}

	void AssimpModel::loadModel(std::string path)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode);
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		}

		m_Directory = path.substr(0, path.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}

	void AssimpModel::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// This node may own multiple meshes 
		for (unsigned int i{ 0 }; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ConvertToEngineMesh(mesh, scene));
		}

		// This node may also own multiple children
		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(node->mChildren[i], scene);
		}

	}

	// BELOW WIP
	Mesh AssimpModel::ConvertToEngineMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		for (unsigned int i{ 0 }; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex{ 0 };
			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z;

			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i]z;

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

		bool meshHasMaterials = (mesh->mMaterialIndex >= 0);
		if (meshHasMaterials)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialsIndex];

			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			g_Textures.insert(g_Textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			g_Textures.insert(g_Textures.end(), specularMaps.begin(), specularMaps.end());
		}
	}

	std::vector<Texture> AssimpModel::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;

		unsigned int numTextures{ mat->GetTextureCount(type) };
		for (unsigned int i{ 0 }; numTextures; ++i)
		{
			aiString relPathToTex;
			mat->GetTexture(type, i, &relPathToTex);

			Texture tex{ relPathToTex };
			tex.type = typeName;
			tex.path = relPathToTex;

			textures.push_back(tex);
		}

		return textures;
	}
}
