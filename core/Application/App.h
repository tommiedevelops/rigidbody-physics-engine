#pragma once

#include "Window.h"
#include "Scene.h"
#include "RenderSystem.h"
#include "AssetManager.h"

namespace PhysicsEngine
{
	class App
	{
	public:
		App();
		void Run();
		void SetCurrentScene(Scene* newScene);
		void LoadModel(std::string pathToModel);
	private:
		Window         m_Window;
		Scene*         m_CurrentScene;
		Renderer       m_Renderer;
		AssetManager   m_AssetManager;
	};
}
