#include <iostream>
#include <GLAD/glad.h>
#include "constants.h"

void prepareOpenGLRender(const float* vertices, std::size_t size)
{
	glViewport(0, 0, Constants::windowWidth, Constants::windowHeight);
	glClearColor(0.1f, 0.9f, 0.4f, 1.0f);

	GLuint VBO;
	int numVertices = 1;
	glGenBuffers(numVertices, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

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

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

