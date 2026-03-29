#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec4 position;
	glm::vec2 uv;
	glm::vec3 normal;
};

class Mesh
{
public:
	std::vector<Vertex>    m_Vertices;
	std::vector<uint32_t>  m_Indices;

	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

private:
	unsigned int VAO, VBO, EBO;

	void SetUpMesh();
};
