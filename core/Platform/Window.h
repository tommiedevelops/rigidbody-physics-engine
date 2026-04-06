#pragma once

#include <glfw/glfw3.h>

namespace PhysicsEngine
{
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

}