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
	}

	void SceneLayer::SetActiveScene(Scene* newScene)
	{
		// probably have to do some queueing or something
		m_ActiveScene = newScene;
	}

}
