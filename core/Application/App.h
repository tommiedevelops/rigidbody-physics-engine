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

		AssetManager* GetAssetsRef()
		{
			return &m_Assets;
		}

		template <typename T>
		T& GetLayer()
		{
			return m_LayerStack.Get<T>();
		}

		void PushLayer(std::shared_ptr<Layer> layer)
		{
			m_LayerStack.PushLayer(layer);
		}

	private:
		Window               m_Window;
		WindowProperties&    m_WindowProperties;
		LayerStack           m_LayerStack;
		AssetManager         m_Assets;
		GameTime             m_GameTime;
	};
}
