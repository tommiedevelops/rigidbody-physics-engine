#include "app.h"

#include "SceneLayer.h"
#include "UILayer.h"

namespace PhysicsEngine
{

	App::App()
		: m_Window{ Window(500,500,"Title") }
		, m_CurrentScene{}
		, m_Assets{}
		, m_GameTime{}
		, m_LayerStack{}
	{
		m_LayerStack.PushLayer(new SceneLayer());
		m_LayerStack.PushLayer(new UILayer());
	}


	void App::SetCurrentScene(Scene* newScene)
	{
		SceneLayer* sceneLayer = m_LayerStack.Get<SceneLayer>();
		sceneLayer->SetActiveScene(newScene);
	};
	
	void App::Run()
	{
		
		while (!m_Window.ShouldClose())
		{
			m_GameTime.Update();

			m_Window.PollEvents();
			m_Window.ProcessInput();

			for (Layer* layer : m_LayerStack.m_Layers)
			{
				layer->OnRender();
				layer->OnUpdate(m_GameTime.GetDeltaTime());
			}
			
			m_Window.SwapBuffers();
		}

		//m_ScriptSystem.CallOnDestroys(m_CurrentScene);
	};
}
