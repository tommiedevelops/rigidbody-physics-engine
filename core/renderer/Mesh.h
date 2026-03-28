#pragma once

class MeshComponent
{
public:
	std::vector<Vertex>    m_Vertices;
	std::vector<uint32_t>  m_Indices;

	Mesh(std::vector<Vertex>   vertices, 
		 std::vector<uint32_t> indices);
private:
	unsigned int VAO, VBO, EBO;

	void SetupMesh();
};
