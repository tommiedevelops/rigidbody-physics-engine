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
	class AssetManager;

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
		virtual ~Scene() = default;

		Entity 
		CreateEntity();

		entt::registry*
		GetRegistry() { return &m_Registry; }

		Entity GetEntity(const std::string& name);

		virtual void SetUp() {};
		void OnRender();
		void OnUpdate(float dt);
		void OnEvent(Event& e);

		void OnAspectRatioChanged(float aspect);
	
		void SetMainCamera(Entity& e);
		CameraComponent* GetMainCamera() { return m_MainCamera; }
		void SetAssetsRef(AssetManager* assetsRef);
	protected:
		AssetManager* m_AssetsRef{ nullptr };
	private:
		entt::registry m_Registry; // can't copy this
		CameraComponent* m_MainCamera{ nullptr }; 
		TransformComponent* m_MainCameraTransform{ nullptr };

		void UpdateCollisions();
		// entities stored here
		void UpdatePhysics(float deltaTime);
		void UpdateScripts(float deltaTime);
		void UpdateForces(float deltaTime);
		void SyncRigidbodyWithTransformComponentCallback(entt::registry& reg, entt::entity e);
		void DestroyScripts();
	};
}
