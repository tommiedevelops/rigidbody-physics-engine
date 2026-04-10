#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <entt/entt.hpp>

namespace PhysicsEngine
{
	class Entity;
	class Camera;
	class Event;

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
		Camera* cam{nullptr}; // might make it entity in future
		PointLight light{}; // single light source for now

		Scene();
		~Scene();

		Entity 
		CreateEntity();

		entt::registry& 
		GetRegistry() { return m_registry; }

		const entt::registry& 
		GetRegistry() const { return m_registry; }

		void Render();
		void Update(float dt);
		void OnEvent(Event& e);

		void SetCameraAspect(float aspect);
	private:
		// entities stored here
		entt::registry m_registry; // can't copy this
		void DestroyScripts();
	};
}
