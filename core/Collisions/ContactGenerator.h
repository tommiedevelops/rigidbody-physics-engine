#pragma once

#include "Collider.h"

namespace PhysicsEngine
{
	class TransformComponent;
	class RigidbodyComponent;

	struct Contact
	{
		glm::vec3   normal;  // contact normal
		glm::vec3   point;   // contact point
		float penetration;   // interpenetration depth

		RigidbodyComponent* bodyA = nullptr;
		RigidbodyComponent* bodyB = nullptr;

		float restitution;
	};

	struct CollisionData
	{
		Contact* contacts; // array of contacts to write into
		unsigned int contactsLeft; // max amount of contacts the array can take
	};

	namespace ContactGenerator
	{
		unsigned int DetectContacts(
			const PrimitiveCollider& first,
			const PrimitiveCollider& second,
			TransformComponent& firstTransform,
			TransformComponent& secondTransform,
			CollisionData* data
		);
	};
		
}