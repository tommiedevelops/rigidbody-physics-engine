#pragma once

#include "Layer.h"
#include "Window.h"
#include "SceneLayer.h"

namespace PhysicsEngine
{

	class GlobalOverlayLayer : public Layer
	{
	private:	
		std::shared_ptr<SceneLayer> m_SceneLayer;
	public:
		GlobalOverlayLayer(std::shared_ptr<SceneLayer> sceneLayer) : m_SceneLayer{ sceneLayer } {}

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnEvent(Event& e) override;
	};

}