#pragma once

namespace PhysicsEngine
{
	class Scene;

	class ScriptSystem
	{
	public:
		ScriptSystem()  = default;
		~ScriptSystem() = default;

		void Update(Scene* scene, float deltaTime);
		void CallOnDestroys(Scene* scene);
	};
}