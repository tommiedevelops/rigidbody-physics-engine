#pragma once

#include <glm/glm.hpp>
#include <glfw/glfw3.h>
#include <optional>

// DEBUG
#include <iostream>

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

		static std::optional<glm::vec2> GetMousePosition() {
			double x, y;

			if (!(GLFW_CURSOR_DISABLED == glfwGetInputMode(s_Window, GLFW_CURSOR)))
				return {};

			glfwGetCursorPos(s_Window, &x, &y);
			return glm::vec2((float)x, (float)y);
		}
		
		static void SetMousePosition(float x, float y) 
		{
			glfwSetCursorPos(s_Window, x, y);
		}

		static void SetCursorEnabled(bool enabled) {
			glfwSetInputMode(s_Window, GLFW_CURSOR,
				enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
		}

		static bool GetCursorEnabled()
		{
			return glfwGetInputMode(s_Window, GLFW_CURSOR);
		}

	private:
		inline static GLFWwindow* s_Window = nullptr;

	};
}