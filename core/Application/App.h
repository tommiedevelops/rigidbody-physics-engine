#pragma once

#include "Window.h"
#include "Scene.h"
#include "RenderSystem.h"
#include "AssetManager.h"
#include "ScriptSystem.h"
#include "GameTime.h"

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
		Scene*         m_CurrentScene;
		Renderer       m_Renderer;
		Assets         m_Assets;
		ScriptSystem   m_ScriptSystem;
		GameTime       m_GameTime;
	};
}
