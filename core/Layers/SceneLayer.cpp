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
		if (m_ActiveScene) m_ActiveScene->OnUpdate(dt);
	}

	void SceneLayer::OnRender()
	{
		if (m_ActiveScene) m_ActiveScene->OnRender();
	}

	void SceneLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowResizedEvent>(
			[this](WindowResizedEvent& e) -> bool
			{
				glViewport(0, 0, e.GetWidth(), e.GetHeight());
				m_CurrentAspect = (float)e.GetWidth() / e.GetHeight();

				if (m_ActiveScene)
					m_ActiveScene->OnAspectRatioChanged(m_CurrentAspect);

				return true;
			}
		);

		if(m_ActiveScene)
			m_ActiveScene->OnEvent(e);
	}

	void SceneLayer::SetActiveScene(const std::string& name)
	{
		m_ActiveScene = m_Factories.at(name)();
		m_ActiveScene->SetAssetsRef(m_AssetsRef);
		m_ActiveScene->SetUp();
		m_ActiveScene->OnAspectRatioChanged(m_CurrentAspect);
	}

}
