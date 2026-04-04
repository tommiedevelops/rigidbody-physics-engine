#include "Model.h"
#include "Texture.h"

#include <iostream>
#include <filesystem>

namespace PhysicsEngine
{
	std::vector<Texture> g_texturesLoaded;

	Model::Model(std::string path)
	{
		LoadModel(path);
	}

	void 
	Model::LoadModel(std::string pathToModel)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(pathToModel, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			throw std::logic_error("There was an error loading the model");
		}

		m_Directory = std::filesystem::path(pathToModel).parent_path().string();

		ProcessNode(scene->mRootNode, scene);
	}

	void 
	Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		// This node may own multiple meshes 
		for (unsigned int i{ 0 }; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ConvertToEngineMesh(mesh, scene));
		}
//DEL
std::cout << node->mName.C_Str() << '\n';
		// This node may also own multiple children
		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(node->mChildren[i], scene);
		}

	}

	std::vector<Texture> 
	Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;

		unsigned int numTextures{ mat->GetTextureCount(type) };
		for (unsigned int i{ 0 }; i < numTextures; ++i)
		{
			aiString texName;
			mat->GetTexture(type, i, &texName);
			
// DEL
std::cout << texName.C_Str() << '\n';
			Texture tex{ m_Directory + '/' + texName.C_Str()};
			tex.type = typeName;
			tex.path = texName.C_Str();

			textures.push_back(tex);
		}

		return textures;
	}

	Mesh 
	Model::ConvertToEngineMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		for (unsigned int i{ 0 }; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex{ };
			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z;

			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;

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
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			m_Textures.insert(m_Textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			m_Textures.insert(m_Textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh{ vertices, indices };
	}

}
