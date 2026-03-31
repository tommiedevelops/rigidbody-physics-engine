#pragma once
#include <entt/entt.hpp>

namespace PhysicsEngine
{
	class Entity
	{
	private:
		const entt::entity m_id;
		const entt::registry& m_registry;
	public:
		Entity(entt::entity id, entt::registry& r);

		template <typename T>
		T& GetComponent();

		template <typename T>
		void AddComponent(T& t);
	};
}

