#include "PhysicsEngine.h"

#include <cstring>

#define MODELS_DIR   "../Assets/models/"
#define TEXTURES_DIR "../Assets/textures/"
#define SHADERS_DIR  "../Assets/shaders/"

int main()
{
	using namespace PhysicsEngine;

	App app{};

	auto& assets = app.GetAssetsRef();
	assets.AddMesh(MODELS_DIR "bunny/bunny.obj", "bunny");
	assets.AddShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag", "default");
	assets.CreateMaterial("default", assets.GetShader("default"), nullptr);

	Scene initialScene{};

	auto e{ initialScene.CreateEntity() };

	auto& meshComp = e.AddComponent<MeshComponent>();
	meshComp.mesh = assets.GetMesh("bunny"); 
	
	auto& matComp  = e.AddComponent<MaterialComponent>();
	matComp.material = assets.GetMaterial("default");

	app.SetCurrentScene(&initialScene);

	app.Run();
}
