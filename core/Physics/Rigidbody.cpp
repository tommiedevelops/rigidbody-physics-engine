#include "Rigidbody.h"

namespace PhysicsEngine
{
	void Rigidbody::UpdateDerivedData()
	{
		glm::mat4 T = glm::translate(glm::mat4(1.0f), linearPosition);
		glm::mat4 R = glm::toMat4(orientation);
		m_ModelMatrix = T * R;
	}
}