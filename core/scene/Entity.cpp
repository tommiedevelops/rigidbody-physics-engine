#include "Entity.h"
#include <iostream>

namespace PhysicsEngine
{
	Entity::Entity(entt::entity id, entt::registry* r)
		: m_id{ id }
		, m_registry{ r }
	{}
}
