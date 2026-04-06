#include "constants.h"

#include "RenderSystem.h"

#include "shader.h"
#include "texture.h"

#include "TransformComponent.h"
#include "MaterialComponent.h"
#include "MeshComponent.h"

#include "scene/scene.h" // The renderer should know the internals of the Scene structure
// should it?

#include <iostream>
#include <entt/entt.hpp>
#include <GLAD/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PhysicsEngine
{

	void Renderer::Render(Scene* scene)
	{
		if (!scene)
		{
			throw std::logic_error("Provided Scene is null");
		}
		glViewport(0, 0, Constants::SCR_WIDTH, Constants::SCR_HEIGHT);
		glClearColor(0.8f, 0.9f, 0.7f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		const entt::registry& creg{ scene->GetRegistry() };

		auto view = creg.view<TransformComponent, MeshComponent, MaterialComponent>();

		view.each([scene](
			const auto entity,
			const auto& transformComp,
			const auto& meshComp,
			const auto& materialComp
		)
		{
			glm::mat4 modelMat { transformComp.GetModelMatrix()   };
			glm::mat4 viewMat  { scene->cam.GetViewMatrix()       };
			glm::mat4 projMat  { scene->cam.GetProjectionMatrix() };

			// Prepare Material data
			Material* material = materialComp.material;

			Shader* s = material->m_Shader;
			unsigned int shaderID = s->GetID();
			s->use(); // bind shader

			int modelLoc = glGetUniformLocation(shaderID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

			int viewLoc = glGetUniformLocation(shaderID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMat));

			int projectionLoc = glGetUniformLocation(shaderID, "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projMat));

			glBindVertexArray(meshComp.mesh->VAO);

			GLsizei numIndices = static_cast<GLsizei>(meshComp.mesh->m_Indices.size());
			glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)0);

			glBindVertexArray(0);
		});
		
	}

}
