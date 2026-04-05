#pragma once

#include "Model.h"
#include <vector>
#include <string>

namespace PhysicsEngine
{
	class Assets
	{
	private:
		std::vector<Model> m_Models;
	public:
		Assets() = default;
		~Assets() = default;

		void AddModel(
			std::string modelName,
			std::string pathToModel,
			std::string pathToVertexShader,
			std::string pathToFragmentShader
		);

		Model* GetModel(std::string modelName);
	};
}