#pragma once

#include "texture.h"
#include "shader.h"
#include <glm/glm.hpp>

namespace PhysicsEngine
{
	struct Material
	{
		glm::vec4 albedo{1.0f};
		float ambientStrength{0.7f};
		float diffuse{0.8f};
		float specular{0.5f};

		std::shared_ptr<Texture>  m_Texture{};
		std::shared_ptr<Shader>  m_Shader{};

		Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture) : m_Shader{ shader }, m_Texture{ texture } {}
	};
}
