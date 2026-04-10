#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace PhysicsEngine
{
	class Rigidbody
	{
	public:
		float inverseMass;

		// linear position of center of mass in world space
		glm::vec3 linearPosition; 

		// orientation of quaternion relative to world space bases
		glm::quat orientation;

		// linear velocity of center of mass in world space
		glm::vec3 linearVelocity;

		// angular velocity of rigidbody relative to world space axes
		glm::vec3 angularVelocity;

		
	private:

		static inline void m_CalculateModelMatrix();
		}
		// Translation * Rotation (No scale here)
		// For going from object space to world space
		glm::mat4 m_ModelMatrix;
	};
}