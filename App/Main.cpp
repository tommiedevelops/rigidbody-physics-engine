#include <iostream>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {

	glfwInit();

	auto window{ glfwCreateWindow(500,500,"Title",NULL,NULL) };

	std::cout << "Hello world!\n";

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
}

