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
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void UILayer::OnUpdate(float dt)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		float value = 0;
		ImGui::Begin("My Window");
		ImGui::Text("Hello");
		ImGui::SliderFloat("Value", &value, 0.0f, 1.0f);
		ImGui::End();

	}

	void UILayer::OnRender()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UILayer::OnEvent(Event& e)
	{
	}
}
