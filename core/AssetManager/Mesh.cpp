#include "Mesh.h"
#include "glad/glad.h"

#include <string>

namespace PhysicsEngine
{
    Mesh::Mesh(
        std::vector<Vertex>   vertices,
        std::vector<uint32_t> indices,
        std::string           name
    )
        : m_Vertices { vertices }
        , m_Indices  { indices  }
        , m_Name     { name     }
    {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
    }

  }
