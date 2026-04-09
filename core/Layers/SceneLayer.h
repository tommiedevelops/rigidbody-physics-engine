#pragma once

#include "Layer.h"
#include "Scene.h"

namespace PhysicsEngine
{
	class SceneLayer : public Layer
	{
	private:
		Scene* m_ActiveScene{ nullptr };
	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnEvent(Event& e) override;

		void SetActiveScene(Scene* m_NewScene);
	};
}