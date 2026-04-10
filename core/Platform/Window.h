#pragma once

#include <glfw/glfw3.h>
#include <functional>
#include <string>


namespace PhysicsEngine
{
	class Event;

	struct WindowProperties
	{
		uint32_t Width; // pixels
		uint32_t Height; // pixels
		std::string Title;

		WindowProperties(
			const std::string& title = "Physics Engine",
			uint32_t width = 1280,
			uint32_t height = 720
		) : Title(title), Width(width), Height(height) {}

	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowProperties& properties);
		~Window();

		bool ShouldClose();
		void PollEvents();
		void SwapBuffers();
		void Start();
		void ProcessInput();

		GLFWwindow* GetNativeWindow() { return m_Window;  }

		void SetEventCallback(const EventCallbackFn& callback)
		{
			m_Data.EventCallback = callback;
		}

	private:

		struct WindowData {
			std::string Title;
			uint32_t Width, Height;
			EventCallbackFn EventCallback;
		};

		GLFWwindow* m_Window;
		WindowData m_Data;
	};

}