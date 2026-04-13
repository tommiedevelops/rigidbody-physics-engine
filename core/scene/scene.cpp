#include "scene.h"

#include "Entity.h"
#include "Components.h"
#include "Rigidbody.h"
#include "AssetManager.h"
#include "ContactGenerator.h"
#include "debug.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace PhysicsEngine
{
	
	void Scene::SyncRigidbodyWithTransformComponentCallback(entt::registry& reg, entt::entity e) 
	{
		auto tr = reg.try_get<TransformComponent>(e);
		auto rb = reg.try_get<RigidbodyComponent>(e);

		if (!tr || !rb) return;

		rb->m_LinearPosition = tr->m_Position;
		rb->m_Orientation = tr->m_Rotation;

		std::cout << "Constructed rigidbody\n";
	}

	Scene::Scene()
	{
		// When a rigidbody is constructed sync RB data to Transform
		// NOTE: DO NOT MODIFY TRANSFORM DIRECTLY. USE RIGIDBODY
		m_Registry.on_construct<RigidbodyComponent>().connect<&Scene::SyncRigidbodyWithTransformComponentCallback>(this);
	}

	Entity Scene::CreateEntity()
	{
		auto e{ Entity(m_Registry.create(), &m_Registry) };
		e.AddComponent<TransformComponent>();
		return e;
	}

	glm::mat4 GetViewMatrix(glm::quat camRotation, glm::vec3 camPosition) {
		glm::vec3 forward = camRotation * glm::vec3(0, 0, -1);
		glm::vec3 up = camRotation * glm::vec3(0, 1, 0);
		return glm::lookAt(camPosition, camPosition + forward, up);
	}
		
	void Scene::OnRender()
	{

		if (!m_MainCamera)
			throw std::logic_error("No main camera was set");

		glClearColor(0.8f, 0.9f, 0.7f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const entt::registry* creg{ GetRegistry() };
		auto view = creg->view<TransformComponent, MeshComponent, MaterialComponent>();

		view.each([this](
			const auto entity,
			const auto& transformComp,
			const auto& meshComp,
			const auto& materialComp
		)
		{
			glm::mat4 modelMat { transformComp.GetModelMatrix()   };
			glm::mat4 viewMat  { GetViewMatrix(m_MainCameraTransform->m_Rotation, m_MainCameraTransform->m_Position) };
			glm::mat4 projMat  { m_MainCamera->GetProjectionMatrix() };
			glm::mat3 normalMat{ glm::transpose(glm::inverse(glm::mat3(modelMat))) };

			// Prepare Material data
			Material* material = materialComp.m_Material;

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

			glBindVertexArray(meshComp.m_Mesh->VAO);

			GLsizei numIndices = static_cast<GLsizei>(meshComp.m_Mesh->m_Indices.size());
			glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)0);

			glBindVertexArray(0);
		});
		
	}

	void Scene::OnUpdate(float deltaTime)
	{
		UpdateScripts(deltaTime);
		UpdateForces(deltaTime);
		UpdatePhysics(deltaTime);
		UpdateCollisions();
	}

	void Scene::UpdateCollisions()
	{
		// maximum amount of contacts system willing to process
		const int MAX_CONTACTS = 256;
		Contact contactArray[MAX_CONTACTS];

		CollisionData data;
		data.contacts = contactArray;
		data.contactsLeft = MAX_CONTACTS;
		
		std::vector<entt::entity> entities;
		auto view = m_Registry.view<ColliderComponent, TransformComponent>();

		view.each([&](auto entity, ColliderComponent&, TransformComponent&) {
			entities.push_back(entity);
			});

		for (int i = 0; i < entities.size(); i++) {
			for (int j = i + 1; j < entities.size(); j++) {
				const auto& colliderA = m_Registry.get<ColliderComponent>(entities[i]);
				auto& transformA = m_Registry.get<TransformComponent>(entities[i]);

				const auto& colliderB = m_Registry.get<ColliderComponent>(entities[j]);
				auto& transformB = m_Registry.get<TransformComponent>(entities[j]);

				for (auto& primA : colliderA.m_Primitives) {
					for (auto& primB : colliderB.m_Primitives) {
						ContactGenerator::DetectContacts(*primA, *primB, transformA, transformB, &data);
					}
				}
			}
		}

		if (data.contactsLeft != MAX_CONTACTS)
		{
			for (auto contact : contactArray)
			{
				std::cout << contact.normal << '\n';
			}
		}

	}

	void Scene::UpdatePhysics(float deltaTime)
	{
		auto view{ m_Registry.view<TransformComponent, RigidbodyComponent>() };

		view.each(
			[deltaTime](auto entity, TransformComponent& tr, RigidbodyComponent& rb)
			{
				rb.Integrate(deltaTime);

				tr.m_Position = rb.m_LinearPosition;
				tr.m_Rotation = rb.m_Orientation;
			}
		);
	}
	
	void Scene::UpdateForces(float deltaTime)
	{
		auto view{ m_Registry.view<RigidbodyComponent, ForceGeneratorComponent>() };

		view.each
		(
			[this, deltaTime](auto entity, auto& rigidbodyComp, auto& forceGenComp)
			{
				ForceGenerator* forceGenerator = forceGenComp.Instance;

				if (!forceGenerator)
				{
					if (!forceGenComp.InstantiateForce) throw std::logic_error("No force generator factory bound");

					forceGenerator = forceGenComp.InstantiateForce();

					if (!forceGenerator) throw std::logic_error("Error instantiating script");

				}

				forceGenerator->UpdateForce(&rigidbodyComp, deltaTime);
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
		auto creg{ GetRegistry() };
		auto view{ creg->view<ScriptComponent>() };
		
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

		auto creg{ GetRegistry() };
		auto view{ creg->view<ScriptComponent>() };
		
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

	void Scene::SetMainCamera(Entity& e)
	{
		if (!e.HasComponent<CameraComponent>())
			throw std::logic_error("Entity does not have a Camera component");
		
		m_MainCamera = &e.GetComponent<CameraComponent>();
		m_MainCameraTransform = &e.GetComponent<TransformComponent>();
	}

	void Scene::OnAspectRatioChanged(float aspect) {
		auto view = m_Registry.view<CameraComponent>();

		view.each([aspect](CameraComponent& cam) {
			cam.m_Aspect = aspect;
			});
	}

	Entity Scene::GetEntity(const std::string& name) 
	{
		auto view = m_Registry.view<NameComponent>();
		Entity result = Entity(entt::null, nullptr);

		view.each(
			[&](auto entity, NameComponent& nc) 
			{
				if (nc.m_Name == name)
					result = Entity(entity, &m_Registry);
			}
		);

		return result;
	}

	void Scene::SetAssetsRef(AssetManager* assetsRef)
	{
		m_AssetsRef = assetsRef;
	}
}

