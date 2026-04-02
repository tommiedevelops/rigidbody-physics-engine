#pragma once

#include "Model.h"
#include <vector>
#include <string>

namespace PhysicsEngine
{
	class AssetManager
	{
	private:
		std::vector<Model> m_Models;
	public:
		AssetManager() = default;
		~AssetManager() = default;

		void LoadModel(std::string path);
	};
}