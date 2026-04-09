#include "SceneLayer.h"

namespace PhysicsEngine
{
	void SceneLayer::OnAttach()
	{
	}

	void SceneLayer::OnDetach()
	{
	}

	void SceneLayer::OnUpdate(float dt)
	{
	}

	void SceneLayer::OnRender()
	{
		if (!m_ActiveScene) return;
	}

	void SceneLayer::OnEvent(Event& e)
	{
	}
}
