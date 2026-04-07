#pragma once

#include "TransformComponent.h"
#include "glm/glm.hpp"

#include "constants.h" // temporary

#include "Entity.h"
#include <vector>


namespace PhysicsEngine
{

	const float aspect = Constants::SCR_WIDTH / Constants::SCR_HEIGHT;

	struct PointLight
	{
	public:
		glm::vec3 position;
		glm::vec3 color;
	};

	class Camera
	{
	public:
		// member variables
		TransformComponent transform{};
		float m_FOVy{ glm::radians(45.0f) };
		float m_Near{ 0.1f };
		float m_Far{ 100.0f };

		Camera() = default;
		~Camera() = default;

		// member functions
		glm::mat4 GetViewMatrix()
		{
			return glm::inverse(transform.GetModelMatrix());
		}

		glm::mat4 GetProjectionMatrix()
		{ 
			return glm::perspective(m_FOVy, aspect, m_Near, m_Far);
		}
	};

	class Scene
	{
	public:
		// member variables
		Camera cam{};
		PointLight light{}; // single light source for now

		// member functions
		Scene() = default;
		~Scene() = default;

		Entity 
		CreateEntity();

		entt::registry& 
		GetRegistry() { return m_registry; }

		const entt::registry& 
		GetRegistry() const { return m_registry; }

		/*
		template <typename T>
		std::array<T> GetAllEntitiesWith<T>();

		template<typename T>

		*/

	private:
		// entities stored here
		entt::registry m_registry; // can't copy this
	};
}
