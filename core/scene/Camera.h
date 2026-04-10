#pragma once

#include <glm/glm.hpp>
#include "Components.h"
#include "constants.h"

namespace PhysicsEngine
{

	class Camera
	{
	public:
		// member variables
		TransformComponent transform{};
		float m_FOVy{ glm::radians(45.0f) };
		float m_Near{ 0.1f };
		float m_Far{ 100.0f };
		float m_Aspect{ 1.0f };

		Camera() = default;
		~Camera() = default;

		// member functions
		glm::mat4 GetViewMatrix()
		{
			return glm::inverse(transform.GetModelMatrix());
		}

		glm::mat4 GetProjectionMatrix()
		{ 
			return glm::perspective(m_FOVy, m_Aspect, m_Near, m_Far);
		}
	};

}