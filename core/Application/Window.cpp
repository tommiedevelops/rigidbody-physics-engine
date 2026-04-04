#include <GLAD/glad.h>
#include "Window.h"

#include <iostream>

namespace PhysicsEngine
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void processInput(GLFWwindow* window)
	{
	}

	Window::Window(int screenWidth, int screenHeight, const char* title)
		: m_glfwWindow{ nullptr }
	{
		glfwInit();

		m_glfwWindow = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);

		if (!m_glfwWindow)
		{
			std::logic_error("Failed to create Window");
			glfwTerminate();
		}

		//set glfw callbacks
		glfwSetFramebufferSizeCallback(m_glfwWindow, framebuffer_size_callback);

		glfwMakeContextCurrent(m_glfwWindow);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::logic_error("Something wrong with glad");
		}

	}

	Window::~Window()
	{
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_glfwWindow);
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_glfwWindow);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::ProcessInput()
	{
		if (glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_glfwWindow, true);
	}
}
