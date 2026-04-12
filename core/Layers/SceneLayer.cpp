#include "Event.h"
#include "MouseEvent.h"
#include "WindowEvent.h"
#include "KeyEvent.h"

#include "SceneLayer.h"

#include <glad/glad.h>
#include <iostream>

namespace PhysicsEngine
{
	bool OnMouseButtonPressed(Event& e)
	{
		std::cout << "Pressed\n";
		return true;
	}

	void SceneLayer::OnAttach()
	{
	}

	void SceneLayer::OnDetach()
	{
	}

	void SceneLayer::OnUpdate(float dt)
	{
		if (!m_ActiveScene) throw std::logic_error("Scene was null");
		m_ActiveScene->OnUpdate(dt);
	}

	void SceneLayer::OnRender()
	{
		if (!m_ActiveScene) throw std::logic_error("Scene was null");
		m_ActiveScene->OnRender();
	}

	void SceneLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowResizedEvent>(
			[this](WindowResizedEvent& e) -> bool
			{
				glViewport(0, 0, e.GetWidth(), e.GetHeight());

				if(m_ActiveScene)
					m_ActiveScene->SetCameraAspect((float)e.GetWidth() / e.GetHeight());

				return true;
			}
		);

		m_ActiveScene->OnEvent(e);
	}

	void SceneLayer::SetActiveScene(Scene* newScene, float screenAspectRatio)
	{
		if (!newScene)
		{
			throw std::logic_error("Provided sceen is null");
			return;
		}

		newScene->SetCameraAspect(screenAspectRatio);
		m_ActiveScene = newScene;
	}

}
