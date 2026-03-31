#include "Entity.h"
#include <iostream>

namespace PhysicsEngine
{
	Entity::Entity(entt::entity id, entt::registry& r)
		: m_id{ id }
		, m_registry{ r }
	{
	}

	template <typename T>
	T& Entity::GetComponent()
	{
		m_registry.get<T>(m_id);
	}

	template <typename T>
	void Entity::AddComponent(T& t)
	{
		m_registry.emplace<T>(m_id);
	};
}
