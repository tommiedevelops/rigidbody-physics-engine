#include "PhysicsEngine.h"


int main()
{
	using namespace PhysicsEngine;

	App app{};

	app.LoadModel("../Assets/backpack/backpack.obj");

	Scene initialScene{};

	auto e{ initialScene.CreateEntity() };
	auto& component = e.AddComponent<RenderComponent>();

	app.SetCurrentScene(&initialScene);
	app.Run();
}
