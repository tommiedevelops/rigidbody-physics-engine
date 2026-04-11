#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <entt/entt.hpp>
#include "RigidbodyForceRegistry.h"

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

		Scene();

		Entity 
		CreateEntity();

		entt::registry& 
		GetRegistry() { return m_Registry; }

		const entt::registry& 
		GetRegistry() const { return m_Registry; }

		void Render();
		void Update(float dt);
		void OnEvent(Event& e);

		void SetCameraAspect(float aspect);
		void SetMainCamera(Entity& e);
	private:
		// entities stored here
		entt::registry m_Registry; // can't copy this

		CameraComponent* m_MainCamera{ nullptr }; 
		TransformComponent* m_MainCameraTransform{ nullptr };
		void UpdatePhysics(float deltaTime);
		void UpdateScripts(float deltaTime);
		void UpdateForces(float deltaTime);
		void SyncRigidbodyWithTransformComponentCallback(entt::registry& reg, entt::entity e);

		void DestroyScripts();
	};
}
