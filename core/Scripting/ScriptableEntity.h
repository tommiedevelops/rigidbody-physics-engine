#pragma once

namespace PhysicsEngine
{
	class Scene;
	class Entity;

	class ScriptableEntity
	{
	public:
		virtual void OnCreate()         {}
		virtual void OnStart()          {}
		virtual void OnUpdate(float dt) {}
		virtual void OnDestroy()        {}

		virtual ~ScriptableEntity() = default;
		ScriptableEntity() = default;

	protected:
		template <typename T>
		T& GetComponent() const;

		template <typename T>
		bool HasComponent() const;

	private:
		Scene*  m_Scene { nullptr };
		Entity* m_Entity{ nullptr };
	};
}
