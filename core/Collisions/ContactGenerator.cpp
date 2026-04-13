#include "ContactGenerator.h"
#include "Collider.h"
#include "Components.h" // better than this?

#include <stdexcept>
#include <iostream> // del

namespace PhysicsEngine
{

	void SphereVsSphere(const SphereCollider& first, const SphereCollider& second, CollisionData* data) 
	{
		//TODO
	}

	void SphereVsBox(const SphereCollider& first, const BoxCollider& second, CollisionData* data) 
	{
		//TODO
	}

	unsigned int SphereVsPlane(const SphereCollider& sphere, const PlaneCollider& plane, TransformComponent& sphereTransform,
		TransformComponent& planeTransform, CollisionData* data)
	{
		// All collision data needs to be in world space

		if (data->contactsLeft <= 0) return 0; //contact budget spent, exit out

		// World space origin on the sphere takes into account
		// the entity's transform but also the collider's offset
		// from the object's origin (omitted for now)
		// ASSUMING SPHERE IS AT ORIGIN (OFFSET = IDENTITY) FOR NOW

		const glm::vec3 sphereOrigin = sphereTransform.Transform(sphere.localPosition);

		const glm::mat3 rotationOnly = glm::mat3(glm::toMat4(planeTransform.m_Rotation));
		glm::vec3 planeNormal = glm::normalize(rotationOnly*plane.m_Normal);

        //                                        translation component of model matrix
		float worldOffset = glm::dot(planeNormal, glm::vec3(planeTransform.GetModelMatrix()[3])) + plane.m_PlaneOffset;

		float radius = sphere.m_Radius;

		float signedDistance = glm::dot(sphereOrigin, planeNormal) - worldOffset;

		if (signedDistance - radius >= 0) return 0; // there is no collision

		Contact* contact = data->contacts;

		contact->normal = planeNormal;
		contact->point = sphereOrigin - planeNormal * (signedDistance + radius);
		contact->penetration = radius - fabsf(signedDistance);

		data->contactsLeft--;
		data->contacts++;  // advance pointer to next slot

		return 1; // 1 contact point
	}

	void BoxVsBox(const BoxCollider& first, const BoxCollider& second, CollisionData* data)
	{
		// TODO
	}

	void BoxVsPlane(const BoxCollider& first, const PlaneCollider& second, CollisionData* data)
	{
		glm::vec3 halfExtents{ first.halfExtents };

		glm::vec3 vertices[8]
		{
			glm::vec3(-halfExtents.x, -halfExtents.y, -halfExtents.z),
			glm::vec3(-halfExtents.x, -halfExtents.y, +halfExtents.z),
			glm::vec3(-halfExtents.x, +halfExtents.y, -halfExtents.z),
			glm::vec3(-halfExtents.x, +halfExtents.y, +halfExtents.z),
			glm::vec3(+halfExtents.x, -halfExtents.y, -halfExtents.z),
			glm::vec3(+halfExtents.x, -halfExtents.y, +halfExtents.z),
			glm::vec3(+halfExtents.x, +halfExtents.y, -halfExtents.z),
			glm::vec3(+halfExtents.x, +halfExtents.y, +halfExtents.z),
		};

		for (unsigned int i{ 0 }; i < 8; ++i)
		{
			// transform vertices by local offset transform
			vertices[i] = glm::vec3(first.GetOffset() * glm::vec4(vertices[i], 1.0f));
		}

		for (auto vertex : vertices)
		{
			float distanceToPlane{ glm::dot(vertex, second.m_Normal) };
			
			if (distanceToPlane <= second.m_PlaneOffset)
			{
				// There's a contact

			}
		}
	}

	void PlaneVsPlane(const PlaneCollider& first, const PlaneCollider& second, CollisionData* data)
	{
		// TODO
	}

	void ContactGenerator::DetectContacts(
		const PrimitiveCollider& first,
		const PrimitiveCollider& second,
		TransformComponent& firstTransform,
		TransformComponent& secondTransform,
		CollisionData* data
	)
	{
		using Type = PrimitiveCollider::PrimitiveType;

		// Extremely ugly code sorry
		switch (first.GetType())
		{
		case Type::SPHERE:
			switch (second.GetType())
			{
			case Type::SPHERE: 
				SphereVsSphere(
					static_cast<const SphereCollider&>(first),
					static_cast<const SphereCollider&>(second),
					data
				);
				break;
			case Type::BOX:
				SphereVsBox(
					static_cast<const SphereCollider&>(first),
					static_cast<const BoxCollider&>(second),
					data
				);
				break;
			case Type::PLANE:
				SphereVsPlane(
					static_cast<const SphereCollider&>(first),
					static_cast<const PlaneCollider&>(second),
					firstTransform,
					secondTransform,
					data
				);
				break;
			case Type::CAPSULE:
				throw std::logic_error("NOT IMPLEMENTED");
				break;
			}
			break;
		case Type::BOX:
			switch (second.GetType())
			{
			case Type::SPHERE: 
				SphereVsBox(
					static_cast<const SphereCollider&>(second),
					static_cast<const BoxCollider&>(first),
					data
				);
				break;
			case Type::BOX:
				BoxVsBox(
					static_cast<const BoxCollider&>(first),
					static_cast<const BoxCollider&>(second),
					data
				);
				break;
			case Type::PLANE:
				BoxVsPlane(
					static_cast<const BoxCollider&>(first),
					static_cast<const PlaneCollider&>(second),
					data
				);
				break;
			case Type::CAPSULE:
				throw std::logic_error("NOT IMPLEMENTED");
				break;
			}
			break;
		case Type::PLANE:
			switch (second.GetType())
			{
			case Type::SPHERE: 
				SphereVsPlane(
					static_cast<const SphereCollider&>(second),
					static_cast<const PlaneCollider&>(first),
					secondTransform,
					firstTransform,
					data
				);
				break;
			case Type::BOX:
				BoxVsPlane(
					static_cast<const BoxCollider&>(second),
					static_cast<const PlaneCollider&>(first),
					data
				);
				break;
			case Type::PLANE:
				PlaneVsPlane(
					static_cast<const PlaneCollider&>(first),
					static_cast<const PlaneCollider&>(second),
					data
				);
				break;
			case Type::CAPSULE:
				throw std::logic_error("NOT IMPLEMENTED");
				break;
			}

			break;
		case Type::CAPSULE:
			throw std::logic_error("NOT IMPLEMENTED");
			break;
		}
	}

}
