#include "AssetManager.h"

namespace PhysicsEngine
{
	void Assets::AddModel(
		std::string modelName, 
		std::string pathToModel,
		std::string pathToVertexShader,
		std::string pathToFragmentShader
	)
	{
		m_Models.push_back(Model(modelName, pathToModel, pathToVertexShader, pathToFragmentShader));
	}

	Model* Assets::GetModel(std::string modelName)
	{
		for (unsigned int i{ 0 }; i < m_Models.size(); ++i)
		{
			if (modelName == m_Models[i].GetName())
				return &m_Models[i];
		}
		return nullptr;
	}
}