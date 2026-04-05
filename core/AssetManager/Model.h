#pragma once

#include "Mesh.h"
#include "texture.h"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

namespace PhysicsEngine
{
	/*
	  An intermediary class for loading Meshes and Materials from various
	  file types using Assimp
	*/

	class Model
	{
	public:
		Model(
			std::string modelName,
			std::string pathToModel,
			std::string pathToVertexShader,
			std::string pathToFragmentShader
		);

		~Model() = default;

		std::string GetName() { return m_Name; }

	private:
		std::vector<Mesh>    m_Meshes;
		std::vector<Texture> m_Textures;
		std::string          m_Directory;
		const std::string    m_Name;

		Shader m_Shader;

		void LoadModel(std::string pathToModel);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ConvertToEngineMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}
