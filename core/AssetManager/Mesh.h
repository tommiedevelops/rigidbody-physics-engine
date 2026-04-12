#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace PhysicsEngine
{
	struct Vertex
	{
		glm::vec4 position{ 0 };
		glm::vec2 uv{ 0 };
		glm::vec3 normal{ 0 };
	};

	class Mesh
	{
	public:
		std::vector<Vertex>    m_Vertices;
		std::vector<uint32_t>  m_Indices;
		unsigned int VAO, VBO, EBO;

		Mesh(const std::string& path);
	private:
		void SetUpMeshRenderBuffers();
	};
}
