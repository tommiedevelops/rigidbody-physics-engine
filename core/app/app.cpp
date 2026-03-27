#include "app.h"

App::App()
	: m_Window{ Window(500,500,"Title") }
	, m_Renderer{ Renderer() }
{}

void App::Run()
{
	while (!m_Window.ShouldClose())
	{
		m_Window.PollEvents();
		m_Window.ProcessInput();

		// render here
//		m_Renderer.Render(m_CurrentScene);

		m_Window.SwapBuffers();
	}
};
