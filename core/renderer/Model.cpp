#include "Model.h"

Model::Model(std::string path)
{
	loadModel(path);
}

void Model::loadModel(std::string path)
{
	//NOOP
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typename)
{
	//NOOP
	return nullptr;
}
