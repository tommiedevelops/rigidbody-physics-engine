#pragma once

#include "IForceGenerator.h"
#include <glm/glm.hpp>

namespace PhysicsEngine
{
	class GravityForceGenerator : public ForceGenerator
	{
		glm::vec3 m_Gravity{ 0.0f, -1.0f, 0.0f };
	public:
		GravityForceGenerator() = default;
		GravityForceGenerator(glm::vec3 gravity) : m_Gravity{ gravity } {}
		void UpdateForce(RigidbodyComponent* rb, float deltaTime) override;
	};
}