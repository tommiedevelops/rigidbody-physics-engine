#pragma once

#include "texture.h"
#include "shader.h"

namespace PhysicsEngine
{
	class Material
	{
	private:
		std::string m_Name{};
	public:
		float albedo{};
		float diffuse{};
		float specular{};

		Texture* m_Texture{};
		Shader*  m_Shader{};

		Material(std::string materialName, Shader* shader, Texture* texture);
	};
}
