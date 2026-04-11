#pragma once

#include "Mesh.h"
#include "Material.h"
#include "ScriptableEntity.h"
#include "IForceGenerator.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


namespace PhysicsEngine
{

	struct CameraComponent
	{
		float m_FOVy{ glm::radians(45.0f) };
		float m_Near{ 0.1f };
		float m_Far{ 100.0f };
		float m_Aspect{ 1.0f };

		glm::mat4 GetProjectionMatrix()
		{
			return glm::perspective(m_FOVy, m_Aspect, m_Near, m_Far);
		}
	};

	struct TransformComponent
	{
		glm::vec3 m_Position{ 0.0f };
		glm::quat m_Rotation{1.0f, 0.0f, 0.0f, 0.0f};
		glm::vec3 m_Scale{ 1.0f };

		glm::mat4 GetModelMatrix() const
		{
			glm::mat4 T = glm::translate(glm::mat4(1.0f), m_Position);
			glm::mat4 R = glm::toMat4(m_Rotation);
			glm::mat4 S = glm::scale(glm::mat4(1.0f), m_Scale);

			return T * R * S;
		}
	};

	struct MeshComponent 
	{
		Mesh* mesh;
	};

	struct MaterialComponent
	{
		Material* material;
	};

	struct ForceGeneratorComponent
	{
		ForceGenerator* Instance = nullptr;

		std::function<ForceGenerator* (void)>  InstantiateForce { nullptr };
		std::function<void (ForceGeneratorComponent*)>   DestroyForce     { nullptr };

		template <typename T>
		void Bind()
		{
			static_assert(std::is_base_of_v<ForceGenerator, T>, "T must derive from IForceGenerator");

			InstantiateForce = []() -> ForceGenerator*
			{
				return new T();
			};

			DestroyForce = [](ForceGeneratorComponent* fg) -> void
			{
				delete fg->Instance;
				fg->Instance = nullptr;
			};

		}

	};

	struct ScriptComponent 
	{
		ScriptableEntity* Instance = nullptr;

		std::function<ScriptableEntity* (void)>  InstantiateScript { nullptr };
		std::function<void (ScriptComponent*)>   DestroyScript     { nullptr };

		bool HasStarted = false;

		template <typename T>
		void Bind()
		{
			static_assert(std::is_base_of_v<ScriptableEntity, T>, "T must derive from ScriptableEntity");

			InstantiateScript = []() -> ScriptableEntity*
			{
				return new T();
			};

			DestroyScript = [](ScriptComponent* sc) -> void
			{
				delete sc->Instance;
				sc->Instance = nullptr;
			};

		}
	};

}