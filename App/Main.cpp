#include "PhysicsEngine.h"


int main()
{
	using namespace PhysicsEngine;

	AssetManager assets{};

	assets.LoadModel("../Assets/backpack/backpack.obj");

	Scene initialScene{};

	auto e{ initialScene.CreateEntity() };
	auto& component = e.AddComponent<RenderComponent>();

	App app{ &initialScene };

	app.Run();
}
