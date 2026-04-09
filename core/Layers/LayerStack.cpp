#include "LayerStack.h"

namespace PhysicsEngine
{
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

}