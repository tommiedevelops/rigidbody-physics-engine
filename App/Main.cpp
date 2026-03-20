#include "renderer/renderer.h"
#include "constants.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

 float vertices[] = { //NDC

	 // positions          // colors
	 0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f
 };

 int indices[] = {
	 0, 1, 2,
 };

 // global constants for now
 void framebuffer_size_callback(GLFWwindow* window, int width, int height)
 {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void setCallBacks(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

int main(int argc, char** argv) {

	glfwInit();

	auto window{ glfwCreateWindow(Constants::windowWidth,Constants::windowHeight,"My Application",NULL,NULL) };

	if (!window)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}

	setCallBacks(window);

	glfwMakeContextCurrent(window); // im guessing this is where the window is linked to opengl?

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	prepareOpenGLRender(vertices, sizeof(vertices), indices, sizeof(indices)); // openGL maintains a global state

	printMaxVertAttribs();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

