#pragma once

#include "Scene.h"

#include <entt/entt.hpp>
#include <memory>

namespace PhysicsEngine
{
	class Event;
	class TransformComponent;
	class Mesh;
	class Shader;
	class Texture;
	class Material;

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
			return m_Scene->GetRegistry()->get<T>(m_Entity);
		}

		template <typename T>
		bool HasComponent() const
		{
			assert(m_Scene);
			return m_Scene->GetRegistry()->all_of<T>(m_Entity);
		}

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Scene->GetRegistry()->emplace<T>(m_Entity, std::forward<Args>(args)...);
		};
		
		Scene* m_Scene{ nullptr };

		std::shared_ptr<Mesh>     LoadMesh(const std::string& path);
		std::shared_ptr<Shader>   LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
		std::shared_ptr<Texture>  LoadTexture(const std::string& path);
		std::shared_ptr<Material> CreateMaterial(const std::string& name, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
		std::unique_ptr<Material> CreateMaterial(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
		std::shared_ptr<Material> GetMaterial(const std::string& name);

		entt::entity m_Entity{ entt::null };
	private:

		friend class Scene;
	};
}
