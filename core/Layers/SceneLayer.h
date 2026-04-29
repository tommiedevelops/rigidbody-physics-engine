#pragma once

#include "Layer.h"
#include "Scene.h"

#include <memory>
#include <string>
#include <functional>

namespace PhysicsEngine
{
	class SceneLayer : public Layer
	{
	private:
		std::unique_ptr<Scene> m_ActiveScene{ nullptr };

		std::unordered_map <std::string, std::function<std::unique_ptr<Scene>()>> m_Factories;

		float  m_CurrentAspect{ 16.0f / 9.0f }; // random

		AssetManager* m_AssetsRef;

		glm::vec2 m_LastMousePosition{};
	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnEvent(Event& e) override;

		void RegisterScene(const std::string& name, std::function<std::unique_ptr<Scene>()> factory)
		{
			m_Factories.emplace(name, factory);
		}

		std::unordered_map<std::string, std::function<std::unique_ptr<Scene>()>>& GetFactories() { return m_Factories; }

		void SetAssetsRef(AssetManager* assetManager) { m_AssetsRef = assetManager; }
		void SetActiveScene(const std::string& name);
	};
}