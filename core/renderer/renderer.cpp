#include "constants.h"

#include "Renderer.h"

#include "shader.h"
#include "texture.h"

#include "Mesh.h"
#include "scene/scene.h" // The renderer should know the internals of the Scene structure
// should it?

#include <iostream>
#include <entt/entt.hpp>
#include <GLAD/glad.h>

namespace PhysicsEngine
{
	class TransformComponent
	{
		glm::mat4 modelMatrix;
	};

	class MaterialComponent
	{
		glm::vec4 albedo;
	};

	void Renderer::Render(Scene* scene)
	{
		const entt::registry& creg{ scene->GetRegistry() };

		// Retrieve all entities with a Transform, Mesh and Material 
	//	auto view = creg.view<TransformComponent, MeshComponent>();

		//view.each([](const auto entity, const auto& transform, const auto& mesh) {
		//	std::cout << "noop";
		//});

	}

	void configureViewport()
	{
		glViewport(0, 0, Constants::SCR_WIDTH, Constants::SCR_HEIGHT);
		glClearColor(0.8f, 0.9f, 0.7f, 1.0f);
	}

	int vertexColorLocation;  // temporary global var

	void prepareVertices(const float* vertices,
		const std::size_t vertices_size,
		const int* indices,
		const std::size_t indices_size
	)
	{

		unsigned int VAO, VBO, EBO;

		Texture texture("../resources/textures/container.jpg");
		Texture texture2("../resources/textures/awesomeface.png");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.getID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2.getID());

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// send data to the VBO
		glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);  // verts
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW); // indices

		// this is how the data is laid out 
		const std::size_t stride = 8 * sizeof(float);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(0); // enable the position data

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1); // color data

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2); // tex coords
	}

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

	void prepareOpenGLRender(const float* vertices,
		const std::size_t vertices_size,
		const int* indicies,
		const std::size_t indicies_size
	)
	{
		configureViewport();

		Shader shader("../resources/shaders/shader.vert", "../resources/shaders/shader.frag");
		shader.use();
		shader.setIntUniform("texture1", 0);
		shader.setIntUniform("texture1", 1);

		shader.setFloatUniform("offset", 0.5f);

		prepareVertices(vertices, vertices_size, indicies, indicies_size);
	}

}
