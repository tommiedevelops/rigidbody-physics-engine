#include "UILayer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream> // temp

namespace PhysicsEngine
{
	// Implement with IMGUI
	void UILayer::OnAttach()
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

	void UILayer::OnDetach()
	{
	}

	void UILayer::OnUpdate(float dt)
	{
	}

	void UILayer::OnRender()
	{
	}

	void UILayer::OnEvent(Event& e)
	{
	}
}
