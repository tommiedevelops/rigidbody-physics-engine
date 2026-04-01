#include "PhysicsEngine.h"

int main()
{
	using namespace PhysicsEngine;

	Scene initialScene{};

	auto e{ initialScene.CreateEntity() };
	auto& component = e.AddComponent<RenderComponent>();

	App app{ &initialScene };

	app.Run();

	/*
	App app();		
	
	auto& s1 = construct_scene1();
	auto& s2 = construct_scene2();
	
	app.AddScene(s1);
	app.AddScene(s2);

	app.Run();
	*/
}
