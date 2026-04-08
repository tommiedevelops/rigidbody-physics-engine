#pragma once

#include <entt/entt.hpp>
#include "Scene.h"

namespace PhysicsEngine
{

	class ScriptableEntity
	{
	public:
		virtual void OnCreate() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnDestroy() = 0;

		virtual ~ScriptableEntity() = default;
		ScriptableEntity() = default;

	protected:

		template <typename T>
		T& GetComponent() const
		{
			assert(m_Scene);
			return m_Scene->GetRegistry().get<T>(m_Entity);
		}

		template <typename T>
		bool HasComponent() const
		{
			assert(m_Scene);
			return m_Scene->GetRegistry().all_of<T>(m_Entity);
		}

	private:
		entt::entity m_Entity{ entt::null };
		Scene* m_Scene{ nullptr };

		friend class ScriptSystem;
	};
}
