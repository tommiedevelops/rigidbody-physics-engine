#pragma once
#include <entt/entt.hpp>

namespace PhysicsEngine
{
	class Entity
	{
	private:
		const entt::entity m_id;
		entt::registry& m_registry;

		// only Scene can create an Entity
		Entity(entt::entity id, entt::registry& r); 
		friend class Scene;

	public:

		Entity(const Entity&) = default; // you can copy an entity
		Entity& operator=(const Entity&) = default; // you can assign an Entity

		entt::entity GetID() { return m_id; }

		template <typename T>
		T& GetComponent()
		{
			return m_registry.get<T>(m_id);
		}

		template <typename T>
		T& AddComponent()
		{
			return m_registry.emplace<T>(m_id);
		};
	};
}

