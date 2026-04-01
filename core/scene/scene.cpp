#include "scene.h"

#include "TransformComponent.h"

namespace PhysicsEngine
{
	Entity Scene::CreateEntity()
	{
		auto e{ Entity(m_registry.create(), m_registry) };
		e.AddComponent<TransformComponent>();
		return e;
	}

}

