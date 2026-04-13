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
		
		struct MeshBounds {
			glm::vec3 min;
			glm::vec3 max;
			glm::vec3 size() const { return max - min; }
			glm::vec3 center() const { return (min + max) * 0.5f; }
		};

		MeshBounds m_Bounds;

		void SetUpMeshRenderBuffers();
	};
}
