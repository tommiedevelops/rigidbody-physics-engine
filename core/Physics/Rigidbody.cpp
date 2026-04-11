#include "Rigidbody.h"

namespace PhysicsEngine
{
	void RigidbodyComponent::UpdateDerivedData()
	{
		glm::mat4 T = glm::translate(glm::mat4(1.0f), linearPosition);
		glm::mat4 R = glm::toMat4(orientation);
		m_ModelMatrix = T * R;
	}

	void RigidbodyComponent::SetInertiaTensor(glm::mat3& inertiaTensor)
	{
		inverseInertiaTensor = glm::inverse(inertiaTensor);
	}

	void RigidbodyComponent::AddLinearForce(const glm::vec3& force)
	{
		m_LinearForceAccumulator += force;
	}

	void RigidbodyComponent::AddForceAtPoint(const glm::vec3& force, const glm::vec3& point)
	{
		m_LinearForceAccumulator += force;

		//  need to convert point to world space before performing cross product
		glm::vec3 worldPoint{ glm::vec3(m_ModelMatrix * glm::vec4(point, 1.0f)) };
		glm::vec3 leverArm = worldPoint - linearPosition;

		m_TorqueAccumulator += glm::cross(leverArm, force);

	}

	void RigidbodyComponent::Integrate(float deltaTime)
	{
		// Calculate linear acceleration
		glm::vec3 linearAcceleration = inverseMass * m_LinearForceAccumulator;

		// Calculate angular acceleration
		glm::vec3 angularAcceleration = inverseInertiaTensor * m_TorqueAccumulator;

		// Update angular & linear values (Euler integration)
		linearVelocity += linearAcceleration * deltaTime;
		linearPosition += linearVelocity * deltaTime;

		glm::vec3 angularVelocity = angularAcceleration * deltaTime;
		glm::quat angularVelocityQuat{ 0.0f, angularVelocity };

		orientation += 0.5f * angularVelocityQuat * orientation * deltaTime;

		UpdateDerivedData();
		// Reset accumulators
		m_LinearForceAccumulator = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TorqueAccumulator		 = glm::vec3(0.0f, 0.0f, 0.0f);
	}

}