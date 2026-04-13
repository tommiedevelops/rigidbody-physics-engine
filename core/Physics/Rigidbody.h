#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace PhysicsEngine
{
	class RigidbodyComponent
	{
	public:

		float m_InverseMass;

		// The inverse of the 3x3 Inertia Tensor which encodes the 
		// rigidbody's mass distribution
		glm::mat3 m_InverseInertiaTensor;

		// For simplicity, the object's local space origin coincides with
		// the center of mass, so I don't need to track c.o.m separately
		glm::vec3 m_LinearPosition; // (c.o.m)

		// orientation of quaternion relative to world space bases
		glm::quat m_Orientation;

		// linear velocity of center of mass in world space
		glm::vec3 m_LinearVelocity;

		// angular velocity of rigidbody relative to world space axes
		glm::vec3 m_AngularVelocity;

		void SetInertiaTensor(glm::mat3& inertiaTensor);
		void UpdateDerivedData();

		// Acts directly on C.O.M (no Torque produced)
		// Force specifed in World Coordinates
		void AddLinearForce(const glm::vec3& force);

		// Force provided in World Coordinates
		// Application point provided in Object Coordinates
		void AddForceAtPoint(const glm::vec3& force, const glm::vec3& point);

		// Updates the rigidbody's angular & linear velocities as well as
		// position and orientation according the the accumulated forces
		// and torques
		void Integrate(float deltaTime);

		bool HasFiniteMass();
		float GetMass();
		void SetMass(float mass);
	private:
		// Translation * Rotation (No scale here)
		// For going from object space to world space
		glm::mat4 m_ModelMatrix;

		glm::mat3 m_InverseInertiaTensorWorldSpace;

		// Accumulators reset to zero at the start of each frame
		glm::vec3 m_LinearForceAccumulator{ 0.0f };
		glm::vec3 m_TorqueAccumulator{ 0.0f };

	};
}