#include "Scenes.h"
#include <memory>

int main()
{
	using namespace PhysicsEngine;

	WindowProperties props{};
	App app{props};

	auto sceneLayer = std::make_shared<SceneLayer>();
	sceneLayer->SetAssetsRef(app.GetAssetsRef());

	sceneLayer->RegisterScene("SpherePlane", []() { return std::make_unique<SpherePlaneCollideScene>(); });
	sceneLayer->RegisterScene("BoxPlane", []() { return std::make_unique<BoxPlaneCollideScene>(); });
	sceneLayer->RegisterScene("BoxSphere", []() { return std::make_unique<SphereBoxCollideScene>(); });
	sceneLayer->RegisterScene("BoxBox", []() { return std::make_unique<BoxBoxCollideScene>(); });
	sceneLayer->RegisterScene("SphereSphere", []() { return std::make_unique<SphereSphereCollideScene>(); });
	sceneLayer->RegisterScene("TennisRacketScene", []() { return std::make_unique<TennisRacketScene>(); });

	sceneLayer->SetActiveScene("TennisRacketScene");

	app.PushLayer(sceneLayer);

	app.Run();
}
