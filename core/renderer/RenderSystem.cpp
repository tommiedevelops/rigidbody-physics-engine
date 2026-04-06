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

namespace PhysicsEngine
{

	void Renderer::Render(Scene* scene)
	{
		if (!scene)
		{
			throw std::logic_error("Provided Scene is null");
		}
		const entt::registry& creg{ scene->GetRegistry() };

		auto view = creg.view<TransformComponent, MeshComponent, MaterialComponent>();

		view.each([scene](
			const auto entity,
			const auto& transform,
			const auto& mesh,
			const auto& material
		)
		{
			glm::mat4 modelMat { transform.GetModelMatrix()       };
			glm::mat4 viewMat  { scene->cam.GetViewMatrix()       };
			glm::mat4 projMat  { scene->cam.GetProjectionMatrix() };


		});
		
	}

	void configureViewport()
	{
		glViewport(0, 0, Constants::SCR_WIDTH, Constants::SCR_HEIGHT);
		glClearColor(0.8f, 0.9f, 0.7f, 1.0f);
	}

	int vertexColorLocation;  // temporary global var
	void printMaxVertAttribs()
	{
		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		std::cout << "The maximum number of attributes is " << nrAttributes << std::endl;

	}

	void render()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//float timeValue = glfwGetTime(); // temporarily allowed here but request from Window in future
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		float greenValue = 1.0f;
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}
