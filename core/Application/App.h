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
		App();
		void Run();
		void SetCurrentScene(Scene* newScene);

		Assets& GetAssetsRef()
		{
			return m_Assets;
		}

	private:
		Window         m_Window;

		// replace below with LayerStack
		Scene*         m_CurrentScene;

		LayerStack     m_LayerStack;
		Assets         m_Assets;
		GameTime       m_GameTime;
	};
}
