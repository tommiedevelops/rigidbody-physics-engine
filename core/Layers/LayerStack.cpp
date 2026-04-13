#include "LayerStack.h"

namespace PhysicsEngine
{
	void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
	{
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

}