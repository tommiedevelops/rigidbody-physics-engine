#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h> // temporary coupling here
#include "constants.h"

void configureViewport()
{
	glViewport(0, 0, Constants::windowWidth, Constants::windowHeight);
	glClearColor(0.8f, 0.9f, 0.7f, 1.0f);
}

int vertexColorLocation;  // temporary global var

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


	vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

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

	unsigned int VAO, VBO, EBO;

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
	const std::size_t stride = 6 * sizeof(float);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0); // enable the position data

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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

		float timeValue = glfwGetTime(); // temporarily allowed here but request from Window in future
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
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
	compileAndBindShaders();
	prepareVertices(vertices, vertices_size, indicies, indicies_size);
}

