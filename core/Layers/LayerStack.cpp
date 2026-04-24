#include "LayerStack.h"

namespace PhysicsEngine
{
	void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
	{
		layer->m_Window = m_Window;
		m_Layers.emplace_back(layer);
		layer->OnAttach();
	}

}