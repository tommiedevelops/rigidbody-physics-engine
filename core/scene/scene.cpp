#include "scene.h"

#include "Entity.h"
#include "Components.h"
#include "Rigidbody.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace PhysicsEngine
{
	
	Entity Scene::CreateEntity()
	{
		auto e{ Entity(m_Registry.create(), m_Registry) };
		e.AddComponent<TransformComponent>();
		return e;
	}

	void Scene::Render()
	{

		if (!m_MainCamera)
			throw std::logic_error("No main camera was set");

		glClearColor(0.8f, 0.9f, 0.7f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const entt::registry& creg{ GetRegistry() };
		auto view = creg.view<TransformComponent, MeshComponent, MaterialComponent>();

		view.each([this](
			const auto entity,
			const auto& transformComp,
			const auto& meshComp,
			const auto& materialComp
		)
		{
			glm::mat4 modelMat { transformComp.GetModelMatrix()   };
			glm::mat4 viewMat  { glm::inverse(m_MainCameraTransform->GetModelMatrix())};
			glm::mat4 projMat  { m_MainCamera->GetProjectionMatrix() };
			glm::mat3 normalMat{ glm::transpose(glm::inverse(glm::mat3(modelMat))) };

			// Prepare Material data
			Material* material = materialComp.material;

			Shader* shader = material->m_Shader;
			unsigned int shaderID = shader->GetID();
			shader->Bind();

			shader->SetVec3Uniform("lightPos", light.position);
			shader->SetVec3Uniform("lightColor", light.color);

			shader->SetVec3Uniform("albedo", material->albedo);
			shader->SetFloatUniform("ambientStrength", material->ambientStrength);

			int modelLoc = glGetUniformLocation(shaderID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

			int viewLoc = glGetUniformLocation(shaderID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));

			int projectionLoc = glGetUniformLocation(shaderID, "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projMat));

			int normalMatLoc = glGetUniformLocation(shaderID, "normalMatrix");
			glUniformMatrix3fv(normalMatLoc, 1, GL_FALSE, glm::value_ptr(normalMat));

			glBindVertexArray(meshComp.mesh->VAO);

			GLsizei numIndices = static_cast<GLsizei>(meshComp.mesh->m_Indices.size());
			glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)0);

			glBindVertexArray(0);
		});
		
	}

	void Scene::Update(float deltaTime)
	{
		UpdateScripts(deltaTime);
		UpdatePhysics(deltaTime);
	}
	void Scene::UpdatePhysics(float deltaTime)
	{
		auto view{ m_Registry.view<TransformComponent, RigidbodyComponent>() };

		view.each(
			[deltaTime](TransformComponent& tr, RigidbodyComponent& rb)
			{
				rb.Integrate(deltaTime);

				tr.position = rb.linearPosition;
				tr.rotation = rb.orientation;
			}
		);
	}
	void Scene::UpdateScripts(float deltaTime)
	{
		auto view{ m_Registry.view<ScriptComponent>() };

		view.each
		(
			[this, deltaTime](auto entity, auto& scriptComp)
			{
				ScriptableEntity* se = scriptComp.Instance;

				if (!se)
				{
					if (!scriptComp.InstantiateScript) throw std::logic_error("No script factory bound");

					se = scriptComp.InstantiateScript();

					if (!se) throw std::logic_error("Error instantiating script");

					se->m_Entity = entity;
					se->m_Scene = this;
					scriptComp.Instance = se;

					se->OnCreate();
				}

				if (!scriptComp.HasStarted)
				{
					se->OnStart();
					scriptComp.HasStarted = true;
				}

				se->OnUpdate(deltaTime);
			}
		);
	}

	void Scene::OnEvent(Event& e)
	{
		auto& creg{ GetRegistry() };
		auto view{ creg.view<ScriptComponent>() };
		
		view.each
		(
			[&e](auto entity, auto& scriptComp)
			{
				ScriptableEntity* se = scriptComp.Instance;

				if (!se) return;

				se->OnEvent(e);
			}
		);


	}

	void Scene::DestroyScripts()
	{

		auto& creg{ GetRegistry() };
		auto view{ creg.view<ScriptComponent>() };
		
		view.each
		(
			[](auto entity, auto& scriptComp)
			{
				if (!scriptComp.Instance) return;
				ScriptableEntity* se = scriptComp.Instance;

				se->OnDestroy();
			}
		);

	}

	void Scene::SetCameraAspect(float aspectRatio)
	{
		m_MainCamera->m_Aspect = aspectRatio;
	}

	void Scene::SetMainCamera(Entity& e)
	{
		if (!e.HasComponent<CameraComponent>())
			std::logic_error("Entity does not have a Camera component");
		
		m_MainCamera = &e.GetComponent<CameraComponent>();
		m_MainCameraTransform = &e.GetComponent<TransformComponent>();
	}
}

