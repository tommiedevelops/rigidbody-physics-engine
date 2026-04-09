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

		template <typename T>
		T* Get()
		{
			static_assert(std::derived_from<T, Layer>, "T must derive from Layer");

			for (Layer* layer : m_Layers)
			{
				if (T* result = dynamic_cast<T*>(layer)) // if i can cast Layer to T, bingo
					return result;
			}

			return nullptr;
		}

		std::vector<Layer*> m_Layers;
	};
}