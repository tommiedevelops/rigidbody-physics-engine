#pragma once

#include <glm/glm.hpp>

namespace PhysicsEngine
{
	class Rigidbody
	{
	private:
		float inverseMass;
		glm::mat3 inertiaTensor;
		glm::vec3 comPos;
	};
}