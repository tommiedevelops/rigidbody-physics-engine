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
