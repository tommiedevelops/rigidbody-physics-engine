#pragma once

#include <entt/entt.hpp>

namespace PhysicsEngine
{
	class Entity
	{
	private:
		entt::entity m_id;
		entt::registry* m_registry;

		Entity(entt::entity id, entt::registry* r); 
		friend class Scene;
	public:

		Entity(const Entity&) = default; // you can copy an entity
		Entity& operator=(const Entity&) = default; // you can assign an Entity

		entt::entity GetID() { return m_id; }

		template <typename T>
		T& GetComponent()
		{
			if (!m_registry) throw std::logic_error("Registry was null");
			return m_registry->get<T>(m_id);
		}

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (!m_registry) throw std::logic_error("Registry was null");
			return m_registry->emplace<T>(m_id, std::forward<Args>(args)...);
		};

		bool IsNull() { return m_id == entt::null || !m_registry; }

		template <typename T>
		bool HasComponent()
		{
			if (!m_registry) throw std::logic_error("Registry was null");
			return m_registry->all_of<T>(m_id);
		};

	};
}

