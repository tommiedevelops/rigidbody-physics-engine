#pragma once

#include "Layer.h"

namespace PhysicsEngine
{
	class SceneLayer : public Layer
	{
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnEvent(Event& e) override;
	};
}