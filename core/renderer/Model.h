#pragma once

#include "Mesh.h"
#include "opengl/texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

class Model
{
public:
	Model();
	~Model() = default;
private:
	std::vector<Mesh> m_Meshes;
	std::string       directory;

	void loadModel(std::string path);

	void processNode(aiNode *node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typename);

};
