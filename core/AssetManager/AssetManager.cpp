#include "AssetManager.h"

namespace PhysicsEngine
{
	void AssetManager::LoadModel(std::string pathToModel)
	{
		m_Models.push_back(Model(pathToModel));
	}
}