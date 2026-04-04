#pragma once

#include "TransformComponent.h"
#include "glm/glm.hpp"

#include "Entity.h"
#include <vector>

namespace PhysicsEngine
{
	class Camera
	{
	public:
		// member variables
		TransformComponent transform{};
		float m_FOVy{ 45.0f };
		float m_Near{ 0.1f };
		float m_Far{ 1000.0f };

		Camera() = default;
		~Camera() = default;

		// member functions
		glm::mat4 GetViewMatrix()
		{
			return glm::inverse(transform.GetModelMatrix());
		}
	};

	class Scene
	{
	public:
		// member variables
		Camera cam{};

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
