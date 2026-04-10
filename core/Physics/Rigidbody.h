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

		// The inverse of the 3x3 Inertia Tensor which encodes the 
		// rigidbody's mass distribution
		glm::mat3 inverseInertiaTensor;

		// For simplicity, the object's local space origin coincides with
		// the center of mass, so I don't need to track c.o.m separately
		glm::vec3 linearPosition; // (c.o.m)

		// orientation of quaternion relative to world space bases
		glm::quat orientation;

		// linear velocity of center of mass in world space
		glm::vec3 linearVelocity;

		// angular velocity of rigidbody relative to world space axes
		glm::vec3 angularVelocity;

		// Member Funcs
		void SetInertiaTensor(glm::mat3& inertiaTensor);
		void UpdateDerivedData();

		// Acts directly on C.O.M (no Torque produced)
		// Force specifed in World Coordinates
		void AddLinearForce(const glm::vec3& force);

		// Force and Point specified in World Coordinates
		void AddForceAtPoint(const glm::vec3& force, const glm::vec3& point);

		// Updates the rigidbody depending on the forces it has 
		// accumulated this frame
		void Integrate(float deltaTime);

	private:
		// Translation * Rotation (No scale here)
		// For going from object space to world space
		glm::mat4 m_ModelMatrix;

		// Accumulators reset to zero at the start of each frame
		float m_LinearForceAccumulator{ 0.0f };
		float m_TorqueAccumulator{ 0.0f };

	};
}