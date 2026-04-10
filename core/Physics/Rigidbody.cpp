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

	void Rigidbody::Integrate(float deltaTime)
	{
		// Reset accumulators
		m_LinearForceAccumulator = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TorqueAccumulator		 = glm::vec3(0.0f, 0.0f, 0.0f);

	}

}