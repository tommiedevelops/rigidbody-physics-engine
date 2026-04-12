#include "app.h"

#include "SceneLayer.h"
#include "UILayer.h"
#include "Event.h"
#include "Input.h"

namespace PhysicsEngine
{

	App::App(WindowProperties& windowProperties)
		: m_Window{windowProperties}
		, m_Assets{}
		, m_GameTime{}
		, m_LayerStack{}
		, m_WindowProperties{windowProperties}
	{
		m_Window.SetEventCallback(
			[this](Event& e) { OnEvent(e); }
		);

		Input::Init(m_Window.GetNativeWindow());

		m_LayerStack.PushLayer(new SceneLayer());
		m_LayerStack.PushLayer(new UILayer());
	}

	void App::SetCurrentScene(Scene* newScene)
	{
		if (!newScene)
			throw std::logic_error("Provided scene was null\n");

		newScene->SetAssetsRef(&m_Assets);
		newScene->SetUp();

		if(!newScene->GetMainCamera())
			throw std::logic_error("No camera found");

		float aspectRatio = (float)m_WindowProperties.Width / m_WindowProperties.Height;

		SceneLayer* sceneLayer = m_LayerStack.Get<SceneLayer>();
		sceneLayer->SetActiveScene(newScene, aspectRatio);
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
			m_Window.ProcessInput();

			m_Window.PollEvents();

			for (Layer* layer : m_LayerStack.GetLayers())
			{
				layer->OnUpdate(m_GameTime.GetDeltaTime());
				layer->OnRender();
			}
			
			m_Window.SwapBuffers();
		}

	};
}
