#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <entt/entt.hpp>

namespace PhysicsEngine
{
	class Entity;
	class Camera;
	class Event;
	struct CameraComponent;
	struct TransformComponent;

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
		PointLight light{}; // single light source for now

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
		void SetMainCamera(Entity& e);
	private:
		// entities stored here
		entt::registry m_registry; // can't copy this

		CameraComponent* m_MainCamera{ nullptr }; 
		TransformComponent* m_MainCameraTransform{ nullptr };

		void DestroyScripts();
	};
}
