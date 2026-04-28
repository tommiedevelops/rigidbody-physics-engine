#include "GlobalOverlayLayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Event.h"
#include "KeyEvent.h"
#include "Input.h"
#include "MouseEvent.h"

#include <iostream> // temp

namespace PhysicsEngine
{
	void GlobalOverlayLayer::OnAttach()
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		if (!m_Window) throw std::logic_error("Window was null");
		auto window{ m_Window->GetNativeWindow() };

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();

		std::cout << "Hello from UI Layer!\n";
	}

	void GlobalOverlayLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void GlobalOverlayLayer::OnUpdate(float dt)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		auto& scenes{ m_SceneLayer->GetFactories() };

		float value = 0;
		ImGui::Begin("Scene Selector");

			for (auto it{ scenes.begin() }; it != scenes.end(); ++it)
			{
				if (ImGui::Button(it->first.c_str()))
				{
					m_SceneLayer->SetActiveScene(it->first);
				}
			}

			ImGui::SliderFloat("Value", &value, 0.0f, 1.0f);
		ImGui::End();
	}

	void GlobalOverlayLayer::OnRender()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GlobalOverlayLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseButtonPressedEvent>(
			[this](MouseButtonPressedEvent& e) -> bool
			{
				auto& io{ ImGui::GetIO() };
				if (io.WantCaptureMouse)
				{ // ImGui consumed this event
					e.SetHandled();
					return true;
				}

				Input::SetCursorEnabled(false);
				return true;
			}
		);

		dispatcher.Dispatch<KeyPressedEvent>(
			[this](KeyPressedEvent& e) -> bool
			{
				if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
				{
					std::cout << "ESCAPE\n";
					Input::SetCursorEnabled(true);
					// Take control of any mouse movements and mouse clicks
				}
				return true;
			}
		);

	}
}
