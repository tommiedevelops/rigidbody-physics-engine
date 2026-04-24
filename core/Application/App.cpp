#include "app.h"

#include "SceneLayer.h"
#include "UILayer.h"
#include "Event.h"
#include "Input.h"

#include <iostream> // for DEBUG

namespace PhysicsEngine
{
	App::App(WindowProperties& windowProperties)
		: m_Window{windowProperties}
		, m_Assets{}
		, m_GameTime{}
		, m_LayerStack{}
		, m_WindowProperties{windowProperties}
	{
		m_LayerStack.SetWindowRef(&m_Window);

		m_Window.SetEventCallback(
			[this](Event& e) { OnEvent(e); }
		);

		Input::Init(m_Window.GetNativeWindow());
	}

	
	void App::OnEvent(Event& e)
	{
		auto& layers{ m_LayerStack.GetLayers() };
		for (auto it = layers.rbegin(); it != layers.rend(); ++it)
		{
			if (e.IsHandled()) break;
			(*it)->OnEvent(e);
		}
	}

	void App::Run()
	{
		
		while (!m_Window.ShouldClose())
		{
			m_GameTime.Update();
			m_Window.ProcessInput();
			m_Window.PollEvents();

			for (auto layer : m_LayerStack.GetLayers())
			{
				layer->OnUpdate(m_GameTime.GetDeltaTime());
				layer->OnRender();
			}

			m_Window.SwapBuffers();
		}

	};
}
