#include "scene.h"

#include "Components.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace PhysicsEngine
{
	Entity Scene::CreateEntity()
	{
		auto e{ Entity(m_registry.create(), m_registry) };
		e.AddComponent<TransformComponent>();
		return e;
	}

	void Scene::Render()
	{
		
		glViewport(0, 0, Constants::SCR_WIDTH, Constants::SCR_HEIGHT);
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
			glm::mat4 viewMat  { cam.GetViewMatrix()       };
			glm::mat4 projMat  { cam.GetProjectionMatrix() };
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
}

