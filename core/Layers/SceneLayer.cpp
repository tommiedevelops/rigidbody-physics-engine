#include "Event.h"
#include "MouseEvent.h"
#include "WindowEvent.h"

#include "SceneLayer.h"

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
		m_ActiveScene->Update(dt);
	}

	void SceneLayer::OnRender()
	{
		if (!m_ActiveScene) throw std::logic_error("Scene was null");
		m_ActiveScene->Render();
	}

	void SceneLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseButtonPressedEvent>(
			[this](MouseButtonPressedEvent& e) -> bool
			{
				return OnMouseButtonPressed(e); 
			}
		);

		dispatcher.Dispatch<WindowResizedEvent>(
			[this](WindowResizedEvent& e) -> bool
			{
				m_ActiveScene->SetCameraAspect((float)e.GetWidth() / e.GetHeight());
				return true;
			}
		);
	}

	void SceneLayer::SetActiveScene(Scene* newScene)
	{
		if (!newScene)
		{
			throw std::logic_error("Provided sceen is null");
			return;
		}

		m_ActiveScene = newScene;
	}

}
