#include "Rigidbody.h"

namespace PhysicsEngine
{
	void Rigidbody::UpdateDerivedData()
	{
		glm::mat4 T = glm::translate(glm::mat4(1.0f), linearPosition);
		glm::mat4 R = glm::toMat4(orientation);
		m_ModelMatrix = T * R;
	}

	void Rigidbody::SetInertiaTensor(glm::mat3& inertiaTensor)
	{
		inverseInertiaTensor = glm::inverse(inertiaTensor);
	}

	void Rigidbody::AddLinearForce(const glm::vec3& force)
	{
		m_LinearForceAccumulator += force;
	}

	void Rigidbody::AddForceAtPoint(const glm::vec3& force, const glm::vec3& point)
	{
		m_LinearForceAccumulator += force;

		//  need to convert point to world space before performing cross product
		glm::vec3 worldPoint{ glm::vec3(m_ModelMatrix * glm::vec4(point, 1.0f)) };
		glm::vec3 leverArm = worldPoint - linearPosition;

		m_TorqueAccumulator += glm::cross(leverArm, force);

	}

	void Rigidbody::Integrate(float deltaTime)
	{
		// Reset accumulators
		m_LinearForceAccumulator = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TorqueAccumulator		 = glm::vec3(0.0f, 0.0f, 0.0f);
	}

}