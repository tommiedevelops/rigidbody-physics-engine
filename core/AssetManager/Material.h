#pragma once

#include "texture.h"
#include "shader.h"
#include <glm/glm.hpp>

namespace PhysicsEngine
{
	struct Material
	{
		glm::vec4 albedo{};
		float ambientStrength{};
		float diffuse{};
		float specular{};

		Texture* m_Texture{};
		Shader*  m_Shader{};

		Material(Shader* shader, Texture* texture) : m_Shader{ shader }, m_Texture{ texture } {}
	};
}
