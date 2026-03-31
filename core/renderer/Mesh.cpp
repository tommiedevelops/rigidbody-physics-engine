#include "Mesh.h"

namespace PhysicsEngine
{
    Mesh::Mesh(
        std::vector<Vertex>   vertices,
        std::vector<uint32_t> indices
    )
    {
        m_Vertices = vertices;
        m_Indices = indices;
        SetUpMesh();
    }

    void Mesh::SetUpMesh()
    {
        // Generate Buffer Objects
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind Buffer Objects
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // Send data to GPU buffer
        glBufferData(
            GL_ARRAY_BUFFER,
            m_Vertices.size() * sizeof(Vertex),
            m_Vertices.data(),
            GL_STATIC_DRAW
        );

        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            m_Indices.size() * sizeof(uint32_t),
            m_Indices.data(),
            GL_STATIC_DRAW
        );

        // Positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        // Vertex Normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);

        // uvs
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glEnableVertexAttribArray(2);

        // unbind the current VAO
        glBindVertexArray(0);
    }
}
