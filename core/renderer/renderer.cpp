#include <iostream>
#include <GLAD/glad.h>
#include "constants.h"

void configureViewport()
{
	glViewport(0, 0, Constants::windowWidth, Constants::windowHeight);
	glClearColor(0.1f, 0.9f, 0.4f, 1.0f);
}

void compileAndBindShaders()
{
	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };

	glShaderSource(vertexShader, 1, &Constants::vertShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragShader{ glCreateShader(GL_FRAGMENT_SHADER) };

	glShaderSource(fragShader, 1, &Constants::fragShaderSource, NULL);
	glCompileShader(fragShader);

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl; 
	}

	GLuint shaderProgram{ glCreateProgram() };

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::LOG::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);


}

void prepareVertices(const float* vertices,
				     const std::size_t vertices_size,
					 const int* indices,
				     const std::size_t indices_size
)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

}

void render()
{
		glClear(GL_COLOR_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void prepareOpenGLRender(const float* vertices,
					     const std::size_t vertices_size,
						 const int* indicies,
						 const std::size_t indicies_size
)
{
	configureViewport();
	compileAndBindShaders();
	prepareVertices(vertices, vertices_size, indicies, indicies_size);
}

