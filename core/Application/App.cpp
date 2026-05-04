#include "app.h"

#include "SceneLayer.h"
#include "GlobalOverlayLayer.h"
#include "Event.h"
#include "Input.h"

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif


#include <iostream> // for DEBUG

namespace PhysicsEngine
{

	static App* s_Instance = nullptr;

	static void EmscriptenMainLoop()
	{
		s_Instance->MainLoop();
	}

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


	void App::MainLoop()
	{
			m_GameTime.Update();
			m_Window.PollEvents();

			for (auto layer : m_LayerStack.GetLayers())
			{
				layer->OnUpdate(m_GameTime.GetDeltaTime());
				layer->OnRender();
			}

			m_Window.SwapBuffers();
	}

	void App::Run()
	{
		s_Instance = this;
		
#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop(EmscriptenMainLoop, 0, 1);
#else
		while (!m_Window.ShouldClose())
		{
			MainLoop();
		}
#endif
	};
}
