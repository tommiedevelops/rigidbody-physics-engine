#pragma once

#include "Layer.h"
#include <vector>

namespace PhysicsEngine
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void PushLayer(Layer* layer);

	private:
		std::vector<Layer*> m_Layers;
	};
}