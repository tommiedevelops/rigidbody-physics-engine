#include "Entity.h"
#include "TransformComponent.h"
#include <iostream>

namespace PhysicsEngine
{
	Entity::Entity(entt::entity id, entt::registry& r)
		: m_id{ id }
		, m_registry{ r }
	{
		// All entities should have a transform
		AddComponent<TransformComponent>();
	}
}
