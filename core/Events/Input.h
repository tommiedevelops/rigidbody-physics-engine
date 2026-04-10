#pragma once

#include <glfw/glfw3.h>

namespace PhysicsEngine
{
	 class Input
	// Implemented as a static class
	{
	public:
		static void Init(GLFWwindow* window) { s_Window = window;  }

		static bool IsKeyDown(int keycode)
		{
			return glfwGetKey(s_Window, keycode) == GLFW_PRESS;
		}

		static bool IsMouseButtonDown(int button)
		{
			return glfwGetMouseButton(s_Window, button) == GLFW_PRESS;
		}

	private:
		inline static GLFWwindow* s_Window = nullptr;

	};
}