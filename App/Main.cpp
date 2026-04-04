#include "PhysicsEngine.h"


int main()
{
	using namespace PhysicsEngine;

	App app{};

	Assets assets{};
	assets.AddModel("backpack", "../Assets/backpack/backpack.obj");
	app.RegisterAssets(&assets);

	Scene initialScene{};

	auto e{ initialScene.CreateEntity() };

	auto& rComp = e.AddComponent<RenderComponent>();
	rComp.model = assets.GetModel("backpack");

	app.SetCurrentScene(&initialScene);

	app.Run();
}
