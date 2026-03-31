#include "scene.h"

namespace PhysicsEngine
{
	Entity Scene::CreateEntity()
	{
		return Entity(m_registry.create(), m_registry);
	}
}

