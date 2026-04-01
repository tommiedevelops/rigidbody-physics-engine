#pragma once

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace PhysicsEngine
{
	struct TransformComponent
	{
		glm::vec3 position{ 0.0f };
		glm::quat rotation{};
		glm::vec3 scale{ 1.0f };

		glm::mat4 GetModelMatrix() const
		{
			glm::mat4 T = glm::translate(glm::mat4(1.0f), position);
			glm::mat4 R = glm::toMat4(rotation);
			glm::mat4 S = glm::scale(glm::mat4(1.0f), scale);

			return T * R * S;
		}

	};
}
