#pragma once

#include "Layer.h"
#include <vector>
#include <memory>

namespace PhysicsEngine
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void PushLayer(std::shared_ptr<Layer> layer);

		template <typename T>
		T* Get()
		{
			static_assert(std::derived_from<T, Layer>, "T must derive from Layer");

			for (auto layer : m_Layers)
			{
				if (T* result = dynamic_cast<T*>(layer)) // if i can cast Layer to T, bingo
					return result;
			}

			return nullptr;
		}

		std::vector<std::shared_ptr<Layer>>& GetLayers()
		{
			return m_Layers;
		}

	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
	};
}