#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Material.h"

#include <vector>
#include <string>

namespace PhysicsEngine
{
	class Assets
	{
	private:
		std::vector<Mesh>     m_Meshes;
		std::vector<Texture>  m_Textures;
		std::vector<Shader>   m_Shaders;

		void ProcessNode(aiNode* node, const aiScene* scene);

		Mesh ConvertToEngineMesh(const aiMesh* mesh, std::string meshName);

	public:
		Assets() = default;
		~Assets() = default;

		void AddMesh(
			std::string pathToModel,
			std::string meshName
		);

		void AddTexture(
			std::string pathToTexture,
			std::string textureName
		);

		void AddShader(
			std::string pathToVertexShader,
			std::string pathToFragmentShader,
			std::string shaderName
		);

		Mesh*    GetMesh(std::string meshName);
		Texture* GetTexture(std::string textureName);
		Shader*  GetShader(std::string shaderName);
	};
}