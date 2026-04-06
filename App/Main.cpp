#include "PhysicsEngine.h"


int main()
{
	using namespace PhysicsEngine;

	App app{};

	Assets assets{};

	app.RegisterAssets(&assets);

	Scene initialScene{};

	auto e{ initialScene.CreateEntity() };

	auto& meshComp = e.AddComponent<MeshComponent>();
	auto& matComp  = e.AddComponent<MaterialComponent>();

	//meshComp.mesh = assets.GetMesh("bunny"); // change to work with mesh directly (screw model)

	app.SetCurrentScene(&initialScene);

	app.Run();
}
