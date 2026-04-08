#include "app.h"

namespace PhysicsEngine
{

	App::App()
		: m_Window{ Window(500,500,"Title") }
		, m_Renderer{ Renderer() }
		, m_CurrentScene{}
		, m_Assets{}
		, m_ScriptSystem{}
		, m_GameTime{}
	{}

	void App::SetCurrentScene(Scene* newScene)
	{
		m_CurrentScene = newScene;
	};
	
	void App::Run()
	{
		
		while (!m_Window.ShouldClose())
		{
			m_GameTime.Update();

			m_Window.PollEvents();
			m_Window.ProcessInput();

			m_ScriptSystem.Update(m_CurrentScene, m_GameTime.GetDeltaTime());

			// render here
			m_Renderer.Render(m_CurrentScene);

			m_Window.SwapBuffers();
		}

		//m_ScriptSystem.CallOnDestroys(m_CurrentScene);
	};
}
