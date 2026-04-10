#include <GLAD/glad.h>

#include "Window.h"
#include "WindowEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

#include <iostream>

namespace PhysicsEngine
{
	Window::Window(const WindowProperties& properties)
	{
		/* ---- Window Init ---- */
		glfwInit();
		m_Window = glfwCreateWindow(properties.Width, properties.Height, properties.Title.c_str(), NULL, NULL);

		if (!m_Window)
		{
			std::logic_error("Failed to create Window");
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::logic_error("Something wrong with glad");

		/* ---- Connecting w/ Event System ---- */

		m_Data.Width  = properties.Width;
		m_Data.Height = properties.Height;
		m_Data.Title  = properties.Title;

		glfwSetWindowUserPointer(m_Window, &m_Data);

		// Mouse Button 
		glfwSetMouseButtonCallback(m_Window, 
			[](GLFWwindow* window, int button, int action, int mods) 
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS: 
					{
						MouseButtonPressedEvent e(button);
						data.EventCallback(e);
						break;
					}
				}
			}
		);
		
		// Window resize
		glfwSetFramebufferSizeCallback(m_Window,
			[](GLFWwindow* window, int width, int height)
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				WindowResizedEvent e(width, height);

				data.Width = width;
				data.Height = height;
				data.EventCallback(e);
			}
		);

		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods) 
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action) 
				{
					case GLFW_PRESS: 
					{
						KeyPressedEvent e(key, 0);
						data.EventCallback(e);
						break;
					}
					case GLFW_REPEAT: 
					{
						KeyPressedEvent e(key, 1);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent e(key);
						data.EventCallback(e);
						break;
					}
				}
			}
		);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::ProcessInput()
	{
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_Window, true);
	}
}
