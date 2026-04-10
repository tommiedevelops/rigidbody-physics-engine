#pragma once

#include "Window.h"
#include "Scene.h"
#include "AssetManager.h"
#include "GameTime.h"
#include "LayerStack.h"

namespace PhysicsEngine
{
	class App
	{
	public:
		App(WindowProperties& windowProperties);
		void Run();
		void SetCurrentScene(Scene* newScene);
		void OnEvent(Event& e);

		Assets& GetAssetsRef()
		{
			return m_Assets;
		}

	private:
		Window            m_Window;
		WindowProperties& m_WindowProperties;
		LayerStack        m_LayerStack;
		Assets            m_Assets;
		GameTime          m_GameTime;
	};
}
