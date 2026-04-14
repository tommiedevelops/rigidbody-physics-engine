#include "PhysicsEngine.h"
#include "LinearMotionDemoScene.h"

#include <memory>

int main()
{
	using namespace PhysicsEngine;

	WindowProperties props{};
	App app{ props };

	auto sceneLayer = std::make_shared<SceneLayer>();
	sceneLayer->SetAssetsRef(app.GetAssetsRef());

	sceneLayer->RegisterScene("LinearMotionScene", []() { return std::make_unique<Talk::LinearMotionDemoScene>(); });

	sceneLayer->SetActiveScene("LinearMotionScene");

	app.PushLayer(sceneLayer);

	app.Run();
	return 0;
}
