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

		Mesh(
			std::vector<Vertex>    vertices,
			std::vector<uint32_t>  indices,
			std::string			   name
		);

		std::string& GetName()
		{
			return m_Name;
		}

	private:
		std::string m_Name;
		unsigned int VAO, VBO, EBO;
		void SetUpMesh();
	};
}
