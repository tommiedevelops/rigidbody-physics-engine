#include "PhysicsEngine.h"


int main()
{
	using namespace PhysicsEngine;

	App app{};

	Assets assets{};

	assets.AddModel(
		"backpack",
		"../Assets/models/bunny/bunny.obj",
		"../Assets/shaders/shader.vert",
		"../Assets/shaders/shader.frag"
	);

	app.RegisterAssets(&assets);

	Scene initialScene{};

	auto e{ initialScene.CreateEntity() };

	auto& rComp = e.AddComponent<ModelComponent>();
	rComp.model = assets.GetModel("backpack");

	app.SetCurrentScene(&initialScene);

	app.Run();
}
