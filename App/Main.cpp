#include "PhysicsEngine.h"
#include "LinearMotionDemoScene.h"
#include "AxisTheoremScene.h"
#include "CollisionResolutionDemoScene.h"
#include "RandomSpheresColliding.h"

#include <memory>

int main()
{
	using namespace PhysicsEngine;

	WindowProperties props{};
	App app{ props };

	auto sceneLayer = std::make_shared<SceneLayer>();
	sceneLayer->SetAssetsRef(app.GetAssetsRef());

	sceneLayer->RegisterScene("LinearMotionScene", []() { return std::make_unique<Talk::LinearMotionDemoScene>(); });
	sceneLayer->RegisterScene("AxisTheoremScene", []() { return std::make_unique<Talk::AxisTheoremScene>(); });
	sceneLayer->RegisterScene("BoxPlane", []() { return std::make_unique<Talk::BoxPlaneCollideScene>(); });
	sceneLayer->RegisterScene("SpherePlane", []() { return std::make_unique<Talk::SpherePlaneCollideScene>(); });
	sceneLayer->RegisterScene("SphereBox", []() { return std::make_unique<Talk::SphereBoxCollideScene>(); });
	sceneLayer->RegisterScene("BoxBox", []() { return std::make_unique<Talk::BoxBoxCollideScene>(); });
	sceneLayer->RegisterScene("WorldsColliding", []() { return std::make_unique<Talk::RandomSpheresCollidingScene>(); });

	sceneLayer->SetActiveScene("SphereBox");

	app.PushLayer(sceneLayer);

	auto uiLayer = std::make_shared<UILayer>();
	app.PushLayer(uiLayer);

	app.Run();
	return 0;
}
