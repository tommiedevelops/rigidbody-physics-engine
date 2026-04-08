#include "ScriptSystem.h"
#include "Scene.h"
#include "ScriptComponent.h"

namespace PhysicsEngine
{
	
	void ScriptSystem::Update(Scene* scene, float deltaTime)
	{
		if (!scene) throw std::logic_error("Scene was null");

		auto& creg{ scene->GetRegistry() };
		auto view{ creg.view<ScriptComponent>() };
		
		view.each
		(
			[scene, deltaTime](auto entity, auto& scriptComp)
			{
				ScriptableEntity* se = scriptComp.Instance;

				if (!se)
				{
					if (!scriptComp.InstantiateScript) throw std::logic_error("No script factory bound");

					se = scriptComp.InstantiateScript();

					if (!se) throw std::logic_error("Error instantiating script");

					se->m_Entity = entity;
					se->m_Scene = scene;
					scriptComp.Instance = se;

					se->OnCreate();
				}

				if (!scriptComp.HasStarted)
				{
					se->OnStart();
					scriptComp.HasStarted = true;
				}

				se->OnUpdate(deltaTime);
			}
		);

	}

	void ScriptSystem::CallOnDestroys(Scene* scene)
	{
		if (!scene) throw std::logic_error("Scene was null");

		auto& creg{ scene->GetRegistry() };
		auto view{ creg.view<ScriptComponent>() };
		
		view.each
		(
			[](auto entity, auto& scriptComp)
			{
				if (!scriptComp.Instance) return;
				ScriptableEntity* se = scriptComp.Instance;

				se->OnDestroy();
			}
		);

	}

}