#pragma once

#include "texture.h"
#include "shader.h"
#include <glm/glm.hpp>

namespace PhysicsEngine
{
	class Material
	{
	private:
		std::string m_Name{};
	public:
		glm::vec4 albedo{};
		float diffuse{};
		float specular{};

		Texture* m_Texture{};
		Shader*  m_Shader{};

		Material(std::string materialName, Shader* shader, Texture* texture);
	};
}
