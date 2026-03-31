#pragma once

#include "scene/scene.h"
#include "renderer/renderer.h"
#include "physics/physics_world.h"
#include "app/window.h"

namespace PhysicsEngine
{
	struct VTable
	{
		// fptrs to callbacks
	};

	class App
	{
	public:
		App(Scene* initialScene);
		void Run();
		void SetCurrentScene(Scene* newScene);
	private:
		Window         m_Window;
		Scene* m_CurrentScene;
		PhysicsWorld   m_PhysicsWorld;
		Renderer       m_Renderer;
		VTable         m_VTable;
	};
}
