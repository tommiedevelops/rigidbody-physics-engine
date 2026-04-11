#pragma once

#include <entt/entt.hpp>
#include "Scene.h"

namespace PhysicsEngine
{
	class Event;
	class TransformComponent;

	class ScriptableEntity
	{
	public:
		virtual void OnCreate() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnDestroy() = 0;
		virtual void OnEvent(Event& e) {};

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

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->GetRegistry().emplace<T>(m_Entity, std::forward<Args>(args)...);
		};
		
	private:
		entt::entity m_Entity{ entt::null };
		Scene* m_Scene{ nullptr };

		friend class Scene;
	};
}
