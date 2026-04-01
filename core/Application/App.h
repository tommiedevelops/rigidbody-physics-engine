#pragma once

#include "Window.h"
#include "Scene.h"
#include "RenderSystem.h"

namespace PhysicsEngine
{
	class App
	{
	public:
		App(Scene* initialScene);
		void Run();
		void SetCurrentScene(Scene* newScene);
	private:
		Window         m_Window;
		Scene*         m_CurrentScene;
		Renderer       m_Renderer;
	};
}
