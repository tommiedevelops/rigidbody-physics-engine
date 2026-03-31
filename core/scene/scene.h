#pragma once

#include "glm/glm.hpp"
#include "Entity.h"
#include <vector>

namespace PhysicsEngine
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity();

		entt::registry& GetRegistry() { return m_registry; }
		const entt::registry& GetRegistry() const { return m_registry; }

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
