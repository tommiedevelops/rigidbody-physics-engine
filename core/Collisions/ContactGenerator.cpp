#include "ContactGenerator.h"
#include "Collider.h"
#include "Components.h" // better than this?

#include <stdexcept>
#include <iostream> // del

#include "debug.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


namespace PhysicsEngine
{

	void SphereVsSphere(const SphereCollider& first, const SphereCollider& second, CollisionData* data) 
	{
		//TODO
	}

	unsigned int SphereVsBox(
		const SphereCollider& sphere,
		const BoxCollider& box,
		TransformComponent& sphereTransform,
		TransformComponent& boxTransform,
		CollisionData* data
	) 
	{
		if (data->contactsLeft <= 0) return 0;
		// IGNORING LOCAL POSITION - ASSUMING SPHERE AT OBJECT ORIGIN'
		//world space
		const glm::vec3 sphereOriginWS = sphereTransform.m_Position;

		// box space
		const glm::vec3 sphereOriginBS{ boxTransform.InverseTransform(sphereOriginWS)};

		const glm::vec3 min{ -box.m_HalfExtents.x, -box.m_HalfExtents.y, -box.m_HalfExtents.z };
		const glm::vec3 max{box.m_HalfExtents.x, box.m_HalfExtents.y, box.m_HalfExtents.z };

		const glm::vec3 closestPointOnBox = glm::clamp(sphereOriginBS, min, max);
		auto closestPointOnBoxWS = boxTransform.Transform(closestPointOnBox);

		auto difference{sphereOriginWS - closestPointOnBoxWS};
		auto differenceLength = glm::length(difference);

		if (static_cast<float>(differenceLength) > sphere.m_Radius) 
			return 0; // no collision

		Contact* contact = data->contacts;

		contact->normal = glm::normalize(difference);
		contact->point = closestPointOnBoxWS;
		contact->penetration = sphere.m_Radius - differenceLength;

		data->contactsLeft--;
		data->contacts++;  // advance pointer to next slot

		return 1; // 1 contact point


	}

	unsigned int SphereVsPlane(const SphereCollider& sphere, const PlaneCollider& plane, TransformComponent& sphereTransform,
		TransformComponent& planeTransform, CollisionData* data)
	{
		// All collision data needs to be in world space

		if (data->contactsLeft <= 0) return 0; //contact budget spent, exit out

		const glm::vec3 sphereOrigin = sphereTransform.Transform(sphere.localPosition);

		const glm::mat3 rotationOnly = glm::mat3(glm::toMat4(planeTransform.m_Rotation));
		glm::vec3 planeNormal = glm::normalize(rotationOnly*plane.m_Normal);

		float worldOffset = glm::dot(planeNormal, glm::vec3(planeTransform.GetModelMatrix()[3])) + plane.m_PlaneOffset;

		float radius = sphere.m_Radius;

		float signedDistance = glm::dot(sphereOrigin, planeNormal) - worldOffset;

		if (signedDistance - radius >= 0) return 0; // there is no collision

		// Add contacts
		Contact* contact = data->contacts;

		contact->normal = planeNormal;
		contact->point = sphereOrigin - planeNormal * (signedDistance + radius);
		contact->penetration = radius - fabsf(signedDistance);

		data->contactsLeft--;
		data->contacts++;  // advance pointer to next slot

		return 1; // 1 contact point
	}

	float ProjectOBB(const glm::vec3& axis, const glm::vec3& center,
		const glm::vec3 axes[3], const glm::vec3& halfExtents) {
		// Project half extents onto axis
		return halfExtents.x * glm::abs(glm::dot(axis, axes[0])) +
			halfExtents.y * glm::abs(glm::dot(axis, axes[1])) +
			halfExtents.z * glm::abs(glm::dot(axis, axes[2]));
	}

	float PenetrationOnAxis(
		const glm::vec3& axis,
		const glm::vec3& centerA, const glm::vec3 axesA[3], const glm::vec3& halfExtentsA,
		const glm::vec3& centerB, const glm::vec3 axesB[3], const glm::vec3& halfExtentsB)
	{
		float projA = ProjectOBB(axis, centerA, axesA, halfExtentsA);
		float projB = ProjectOBB(axis, centerB, axesB, halfExtentsB);

		float distance = glm::abs(glm::dot(centerB - centerA, axis));

		return projA + projB - distance;  // positive = overlap, negative = gap
	}

	unsigned int BoxVsBox(
		const BoxCollider& boxA, const BoxCollider& boxB,
		TransformComponent& transformA, TransformComponent& transformB,
		CollisionData* data)
	{
		if (data->contactsLeft <= 0) return 0;

		// Get world space axes for each box
		glm::vec3 axesA[3] = {
			glm::normalize(transformA.m_Rotation * glm::vec3(1, 0, 0)),
			glm::normalize(transformA.m_Rotation * glm::vec3(0, 1, 0)),
			glm::normalize(transformA.m_Rotation * glm::vec3(0, 0, 1))
		};
		glm::vec3 axesB[3] = {
			glm::normalize(transformB.m_Rotation * glm::vec3(1, 0, 0)),
			glm::normalize(transformB.m_Rotation * glm::vec3(0, 1, 0)),
			glm::normalize(transformB.m_Rotation * glm::vec3(0, 0, 1))
		};

		glm::vec3 centerA = transformA.m_Position;
		glm::vec3 centerB = transformB.m_Position;
		glm::vec3 halfA = boxA.m_HalfExtents * transformA.m_Scale;
		glm::vec3 halfB = boxB.m_HalfExtents * transformB.m_Scale;

		// Track best axis (smallest penetration)
		float     bestPenetration = FLT_MAX;
		glm::vec3 bestAxis;

		// Test all 15 axes
		glm::vec3 axes[15] = {
			axesA[0], axesA[1], axesA[2],  // face normals of A
			axesB[0], axesB[1], axesB[2],  // face normals of B
			// edge cross products
			glm::cross(axesA[0], axesB[0]),
			glm::cross(axesA[0], axesB[1]),
			glm::cross(axesA[0], axesB[2]),
			glm::cross(axesA[1], axesB[0]),
			glm::cross(axesA[1], axesB[1]),
			glm::cross(axesA[1], axesB[2]),
			glm::cross(axesA[2], axesB[0]),
			glm::cross(axesA[2], axesB[1]),
			glm::cross(axesA[2], axesB[2])
		};

		for (auto& axis : axes) {
			// Skip near-zero axes (degenerate cross products)
			if (glm::length(axis) < 0.001f) continue;
			axis = glm::normalize(axis);

			float penetration = PenetrationOnAxis(
				axis, centerA, axesA, halfA, centerB, axesB, halfB);

			if (penetration < 0) return 0;  // gap found — no collision

			if (penetration < bestPenetration) {
				bestPenetration = penetration;
				bestAxis = axis;
			}
		}

		// Make sure normal points from B to A
		if (glm::dot(bestAxis, centerA - centerB) < 0)
			bestAxis = -bestAxis;

		Contact* contact = data->contacts;
		contact->normal = bestAxis;
		contact->penetration = bestPenetration;
		contact->point = centerA - bestAxis * bestPenetration;  // approximate
		data->contactsLeft--;
		data->contacts++;
		return 1;
	}

	int BoxVsPlane(
		const BoxCollider& box,
		const PlaneCollider& plane,
		TransformComponent& boxTransform,
		TransformComponent& planeTransform,
		CollisionData* data
	)
	{
		// COLLISION DETECTION PERFORMED IN WORLD SPACE
		// ASSUMING NO LOCAL OFFSET TRANSFORM (ITS AT THE ORIGIN)

		glm::vec3 halfExtents{ box.m_HalfExtents };

		glm::vec3 vertices[8]
		{
			boxTransform.Transform(glm::vec3(-halfExtents.x, -halfExtents.y, -halfExtents.z)),
			boxTransform.Transform(glm::vec3(-halfExtents.x, -halfExtents.y, +halfExtents.z)),
			boxTransform.Transform(glm::vec3(-halfExtents.x, +halfExtents.y, -halfExtents.z)),
			boxTransform.Transform(glm::vec3(-halfExtents.x, +halfExtents.y, +halfExtents.z)),
			boxTransform.Transform(glm::vec3(+halfExtents.x, -halfExtents.y, -halfExtents.z)),
			boxTransform.Transform(glm::vec3(+halfExtents.x, -halfExtents.y, +halfExtents.z)),
			boxTransform.Transform(glm::vec3(+halfExtents.x, +halfExtents.y, -halfExtents.z)),
			boxTransform.Transform(glm::vec3(+halfExtents.x, +halfExtents.y, +halfExtents.z))
		};

		const glm::mat3 rotationOnly = glm::mat3(glm::toMat4(planeTransform.m_Rotation));
		glm::vec3 planeNormal = glm::normalize(rotationOnly*plane.m_Normal);

		float worldOffset = glm::dot(planeNormal, glm::vec3(planeTransform.GetModelMatrix()[3])) + plane.m_PlaneOffset;

		int numContacts = 0;

		for (auto vertex : vertices)
		{
			float distanceToPlane{ glm::dot(vertex, planeNormal) };
			
			if (distanceToPlane <= worldOffset)
			{
				// There's a contact
				Contact* contact = data->contacts;
				contact->normal = planeNormal;

				contact->point = vertex;
				contact->penetration = distanceToPlane;

				data->contactsLeft--;
				data->contacts++;  // advance pointer to next slot

				numContacts++;
			}
		}

		return numContacts;
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
					firstTransform,
					secondTransform,
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
					secondTransform,
					firstTransform,
					data
				);
				break;
			case Type::BOX:
				BoxVsBox(
					static_cast<const BoxCollider&>(first),
					static_cast<const BoxCollider&>(second),
					firstTransform,
					secondTransform,
					data
				);
				break;
			case Type::PLANE:
				BoxVsPlane(
					static_cast<const BoxCollider&>(first),
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
					secondTransform,
					firstTransform,
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
