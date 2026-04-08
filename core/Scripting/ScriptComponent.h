#pragma once

#include "ScriptableEntity.h"
#include <type_traits>
#include <functional>

namespace PhysicsEngine
{
	struct ScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		std::function<ScriptableEntity* (void)>  InstantiateScript { nullptr };
		std::function<void (ScriptComponent*)>   DestroyScript     { nullptr };

		template <typename T>
		void Bind()
		{
			static_asset(std::is_base_of_v<ScriptableEntity, T>, "T must derive from ScriptableEntity");

			InstantiateScript = []() -> ScriptableEntity*
			{
				return new T();
			};

			DestroyScript = [](ScriptComponent* sc) -> void
			{
				delete sc->Instance;
				sc->Instance = nullptr;
			};

		}
	};
}
