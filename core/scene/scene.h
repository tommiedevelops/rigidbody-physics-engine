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
		glm::vec3 position{ 10, 100, 10 };
		glm::vec3 color{ 1,1,1 };
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

		void DestroyEntity(entt::entity e);

		virtual void SetUp() {};
		void OnRender();
		void OnUpdate(float dt);
		void OnEvent(Event& e);

		void OnAspectRatioChanged(float aspect);
	
		void SetMainCamera(Entity& e);
		CameraComponent* GetMainCamera() { return m_MainCamera; }
		void SetAssetsRef(AssetManager* assetsRef);
		AssetManager* GetAssetsRef() const { return m_AssetsRef; }
	protected:
		AssetManager* m_AssetsRef{ nullptr };
	private:
		entt::registry m_Registry; // can't copy this
		CameraComponent* m_MainCamera{ nullptr }; 
		TransformComponent* m_MainCameraTransform{ nullptr };

		void UpdateCollisions(float deltaTime);
		void UpdatePhysics(float deltaTime);
		void UpdateScripts(float deltaTime);
		void UpdateForces(float deltaTime);
		void SyncRigidbodyWithTransformComponentCallback(entt::registry& reg, entt::entity e);
		void DestroyScripts();
	};
}
