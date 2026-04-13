#pragma once

#include "Collider.h"

namespace PhysicsEngine
{
	class TransformComponent;

	struct Contact
	{
		glm::vec3   normal;  // contact normal
		glm::vec3   point;   // contact point
		float penetration;   // interpenetration depth
	};

	struct CollisionData
	{
		Contact* contacts; // array of contacts to write into
		unsigned int contactsLeft; // max amount of contacts the array can take
	};

	class ContactGenerator
	{
	public:
		static void DetectContacts(
			const PrimitiveCollider& first,
			const PrimitiveCollider& second,
			TransformComponent& firstTransform,
			TransformComponent& secondTransform,
			CollisionData* data
		);
	};
		
}