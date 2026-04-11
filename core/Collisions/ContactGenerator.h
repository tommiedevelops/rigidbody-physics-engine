#pragma once

#include "Collider.h"

namespace PhysicsEngine
{
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
		void DetectContacts(
			const PrimitiveCollider& first,
			const PrimitiveCollider& second,
			CollisionData* data
		);
	};
		
}