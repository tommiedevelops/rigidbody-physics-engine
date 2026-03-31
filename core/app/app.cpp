#include "app.h"
#include "renderer/Model.h" // remove (just doing for compilation)

namespace PhysicsEngine
{

	App::App(Scene* initialScene)
		: m_Window{ Window(500,500,"Title") }
		, m_Renderer{ Renderer() }
		, m_CurrentScene{ initialScene }
	{
	}

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
