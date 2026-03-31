#pragma once

#include "Mesh.h"
#include "texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>


/*
  An intermediary class for loading Meshes and Materials from various
  file types using Assimp
*/

class AssimpModel
{
public:
	AssimpModel(std::string pathToModel);
	~AssimpModel() = default;
private:
	std::vector<Mesh> m_Meshes;
	std::string       m_Directory;

	void loadModel(std::string path);

	void ProcessNode(aiNode *node, const aiScene* scene);
	Mesh ConvertToEngineMesh(aiMesh* mesh, const aiScene* scene);
	
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typename);

};
