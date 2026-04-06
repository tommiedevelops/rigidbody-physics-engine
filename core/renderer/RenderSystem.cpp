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
			glm::mat4 modelMat { transformComp.GetModelMatrix()       };
			glm::mat4 viewMat  { scene->cam.GetViewMatrix()       };
			glm::mat4 projMat  { scene->cam.GetProjectionMatrix() };

			// Prepare Mesh Data
			unsigned int VAO = meshComp.mesh->VAO;
			unsigned int VBO = meshComp.mesh->VBO;
			unsigned int EBO = meshComp.mesh->EBO;
			auto& vertices = meshComp.mesh->m_Vertices;
			auto& indices = meshComp.mesh->m_Indices;

			// Bind Buffer Objects
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

			// Send data to GPU buffer
			glBufferData(
				GL_ARRAY_BUFFER,
				vertices.size() * sizeof(Vertex),
				vertices.data(),
				GL_STATIC_DRAW
			);

			glBufferData(
				GL_ELEMENT_ARRAY_BUFFER,
				indices.size() * sizeof(uint32_t),
				indices.data(),
				GL_STATIC_DRAW
			);

			// Positions
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);

			// Vertex Normals
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(1);

			// uvs
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
			glEnableVertexAttribArray(2);


			// Prepare Material data
			Material* material = materialComp.material;

			Shader* s = material->m_Shader;
			unsigned int shaderID = s->GetID();

			int modelLoc = glGetUniformLocation(shaderID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

			int viewLoc = glGetUniformLocation(shaderID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

			int projectionLoc = glGetUniformLocation(shaderID, "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(modelMat));

			s->use(); // bind shader

			const int numIndices = meshComp.mesh->m_Indices.size();

			glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)0);

			glBindVertexArray(0);
		});
		
	}

	void configureViewport()
	{
		glViewport(0, 0, Constants::SCR_WIDTH, Constants::SCR_HEIGHT);
		glClearColor(0.8f, 0.9f, 0.7f, 1.0f);
	}

}
