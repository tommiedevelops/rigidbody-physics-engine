#include "app.h"

#include "SceneLayer.h"
#include "UILayer.h"

namespace PhysicsEngine
{

	App::App(WindowProperties& windowProperties)
		: m_Window{windowProperties}
		, m_CurrentScene{}
		, m_Assets{}
		, m_GameTime{}
		, m_LayerStack{}
	{
		m_Window.SetEventCallback(
			[this](Event& e) { OnEvent(e); }
		);

		m_LayerStack.PushLayer(new SceneLayer());
		m_LayerStack.PushLayer(new UILayer());
	}

	void App::SetCurrentScene(Scene* newScene)
	{
		SceneLayer* sceneLayer = m_LayerStack.Get<SceneLayer>();
		sceneLayer->SetActiveScene(newScene);
	};
	
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

			// Poll Events here, create Event objects
			m_Window.PollEvents();
			m_Window.ProcessInput();

			for (Layer* layer : m_LayerStack.GetLayers())
			{
				layer->OnUpdate(m_GameTime.GetDeltaTime());
				layer->OnRender();
			}
			
			m_Window.SwapBuffers();
		}

		//m_ScriptSystem.CallOnDestroys(m_CurrentScene);
	};
}
