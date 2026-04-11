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
		void UpdateForce(RigidbodyComponent* rb, float deltaTime) override;
	};
}