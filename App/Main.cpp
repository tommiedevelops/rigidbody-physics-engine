#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main(int argc, char** argv) {

	glfwInit();

	auto window{ glfwCreateWindow(500,500,"Title",NULL,NULL) };

	if (!window)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	std::cout << "Hello world!\n";

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
}

