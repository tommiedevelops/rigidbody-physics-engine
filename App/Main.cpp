#include "PhysicsEngine.h"

int main()
{
	using namespace PhysicsEngine;

	Scene initialScene{};

	auto e{ initialScene.CreateEntity() };
	auto& component = e.AddComponent<RenderComponent>();

	App app{ &initialScene };

	app.Run();
}
