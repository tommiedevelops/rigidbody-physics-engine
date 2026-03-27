#include "scene.h"

Entity Scene::CreateEntity()
{
	return Entity(m_registry.create(), m_registry);
}


