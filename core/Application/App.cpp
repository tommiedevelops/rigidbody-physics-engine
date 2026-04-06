#include "app.h"

namespace PhysicsEngine
{

	App::App()
		: m_Window{ Window(500,500,"Title") }
		, m_Renderer{ Renderer() }
		, m_CurrentScene{}
		, m_Assets{}
	{}

	void App::SetCurrentScene(Scene* newScene)
	{
		m_CurrentScene = newScene;
	};
	
	void App::Run()
	{
		while (!m_Window.ShouldClose())
		{
			m_Window.PollEvents();
			m_Window.ProcessInput();

			// render here
			m_Renderer.Render(m_CurrentScene);

			m_Window.SwapBuffers();
		}
	};
}
