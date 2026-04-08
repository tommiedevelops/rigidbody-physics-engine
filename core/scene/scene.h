#pragma once

#include "Entity.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <vector>


namespace PhysicsEngine
{
	struct PointLight
	{
	public:
		glm::vec3 position;
		glm::vec3 color;
	};

	class Scene
	{
	public:
		// member variables
		Camera cam{}; // might make it entity in future
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

	private:
		// entities stored here
		entt::registry m_registry; // can't copy this
	};
}
