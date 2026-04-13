#include "Rigidbody.h"

namespace PhysicsEngine
{
	void RigidbodyComponent::UpdateDerivedData()
	{
		glm::mat4 T = glm::translate(glm::mat4(1.0f), m_LinearPosition);
		glm::mat4 R = glm::toMat4(m_Orientation);
		m_InverseInertiaTensorWorldSpace = glm::mat3(R) * m_InverseInertiaTensor * glm::mat3(glm::transpose(R));
		m_ModelMatrix = T * R;
	}

	void RigidbodyComponent::SetInertiaTensor(glm::mat3& inertiaTensor)
	{
		m_InverseInertiaTensor = glm::inverse(inertiaTensor);
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
		glm::vec3 leverArm = worldPoint - m_LinearPosition;

		m_TorqueAccumulator += glm::cross(leverArm, force);

	}

	void RigidbodyComponent::Integrate(float deltaTime)
	{
		// Calculate linear acceleration
		glm::vec3 linearAcceleration = m_InverseMass * m_LinearForceAccumulator;

		// Calculate angular acceleration
		glm::vec3 angularAcceleration = m_InverseInertiaTensorWorldSpace * m_TorqueAccumulator;

		// Update angular & linear values (Euler integration)
		m_LinearVelocity += linearAcceleration * deltaTime;
		m_LinearPosition += m_LinearVelocity * deltaTime;

		m_AngularVelocity += angularAcceleration * deltaTime;
		glm::quat angularVelocityQuat{ 0.0f, m_AngularVelocity.x, m_AngularVelocity.y, m_AngularVelocity.z };

		m_Orientation += 0.5f * angularVelocityQuat * m_Orientation * deltaTime;
		m_Orientation = glm::normalize(m_Orientation);

		UpdateDerivedData();
		// Reset accumulators
		m_LinearForceAccumulator = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TorqueAccumulator		 = glm::vec3(0.0f, 0.0f, 0.0f);
	}

    bool RigidbodyComponent::HasFiniteMass()
	{
		return m_InverseMass != 0;
	}

	void RigidbodyComponent::SetMass(float mass)
	{
		m_InverseMass = 1.0f / mass;
	}

	float RigidbodyComponent::GetMass()
	{
		return (float)1 / m_InverseMass;
	}
}