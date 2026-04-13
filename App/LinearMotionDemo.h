#include "PhysicsEngine.h"
#include "Common.h"

namespace Talk
{
	using namespace PhysicsEngine;

	class ObjectScript : public ScriptableEntity
	{
		void OnCreate() override
		{

		}

		void OnStart() override
		{
			AddComponent<MeshComponent>(MODELS_DIR "cube.obj");
			AddComponent<MaterialComponent>()
		}

		void OnUpdate(float dt) override
		{

		}

		void OnDestroy() override;
	};

	class LinearMotionDemoScene : public Scene
	{
		void SetUp() override
		{
			auto e{ CreateEntity() };
			e.AddComponent<ScriptComponent>().Bind<ObjectScript>();
		}
	};
}