#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

const char* vertShaderSource
{
	"#version 420 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0"
};

const char* fragShaderSource
{
	"#version 420 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
	"}\0"
};


int windowWidth { 500 };
int windowHeight{ 500 };

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char** argv) {

	glfwInit();
	auto window{ glfwCreateWindow(windowWidth,windowHeight,"Title",NULL,NULL) };

	// Set Callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!window)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//opengl stuff
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(0.1f, 0.9f, 0.4f, 1.0f);

	unsigned int VBO_id;
	int numVertices = 1;
	glGenBuffers(numVertices, &VBO_id);

	unsigned int VAO_id;
	glGenVertexArrays(1, &VAO_id);

	unsigned int vertShader_id;
	vertShader_id = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertShader_id, 1, &vertShaderSource, NULL);
	glCompileShader(vertShader_id);

	unsigned int fragShader_id;
	fragShader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader_id, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader_id);

	int success_vert;
	int success_frag;

	char infoLog_vert[512];
	char infoLog_frag[512];

	glGetShaderiv(vertShader_id, GL_COMPILE_STATUS, &success_vert);
	glGetShaderiv(fragShader_id, GL_COMPILE_STATUS, &success_frag);

	if (!success_vert)
	{
		glGetShaderInfoLog(vertShader_id, 512, NULL, infoLog_vert);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog_vert << std::endl;
	}

	if (!success_frag)
	{
		glGetShaderInfoLog(fragShader_id, 512, NULL, infoLog_frag);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog_frag << std::endl; 
	}

	unsigned int shaderProgram_id;
	shaderProgram_id = glCreateProgram();

	glAttachShader(shaderProgram_id, vertShader_id);
	glAttachShader(shaderProgram_id, fragShader_id);
	glLinkProgram(shaderProgram_id);

	int success_prog;
	glGetProgramiv(shaderProgram_id, GL_LINK_STATUS, &success_prog);
	char infoLog_prog[512];
	
	if (!success_prog)
	{
		glGetProgramInfoLog(shaderProgram_id, 512, NULL, infoLog_prog);
		std::cout << "ERROR::LOG::SHADER::LINKING_FAILED\n" << infoLog_prog << std::endl;
	}

	glBindVertexArray(VAO_id);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram_id);

	glDeleteShader(vertShader_id);
	glDeleteShader(fragShader_id);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	std::cout << "Window is finished\n";
	return 0;
}

