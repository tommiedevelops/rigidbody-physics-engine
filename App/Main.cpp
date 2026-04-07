#include "PhysicsEngine.h"

#define MODELS_DIR   "../Assets/models/"
#define TEXTURES_DIR "../Assets/textures/"
#define SHADERS_DIR  "../Assets/shaders/"

int main()
{
	using namespace PhysicsEngine;

	App app{};

	auto& assets = app.GetAssetsRef();
	assets.AddMesh(MODELS_DIR "bunny/bunny.obj", "bunny");
	assets.AddMesh(MODELS_DIR "cube.obj", "cube");

	assets.AddShader(SHADERS_DIR "shader.vert", SHADERS_DIR "shader.frag", "default");

	assets.CreateMaterial("default", assets.GetShader("default"), nullptr);

	Scene initialScene{};
	initialScene.light.direction = glm::vec3(-1.0f, -1.0f, -1.0f);

	auto e{ initialScene.CreateEntity() };

	auto& meshComp = e.AddComponent<MeshComponent>();
	meshComp.mesh = assets.GetMesh("cube"); 
	
	auto& matComp  = e.AddComponent<MaterialComponent>();
	matComp.material = assets.GetMaterial("default");

	auto& transformComp = e.GetComponent<TransformComponent>();
	transformComp.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transformComp.rotation = glm::quat(1.0f, 0.3f, 0.2f, 0.1f);
	transformComp.position = glm::vec3(0.0f, 0.0f, -10.0f);

	//initialScene.cam.transform.position = glm::vec3(1.0f, 0.0f, 5.0f);

	app.SetCurrentScene(&initialScene);

	app.Run();
}
