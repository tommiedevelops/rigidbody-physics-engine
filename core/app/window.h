#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h> 

class Window
{
public:

	Window(int, int, const char*);
	~Window();

	bool ShouldClose();
	void PollEvents();
	void SwapBuffers();
	void Start();
	void ProcessInput();

private:
	GLFWwindow* m_glfwWindow;
};

#endif