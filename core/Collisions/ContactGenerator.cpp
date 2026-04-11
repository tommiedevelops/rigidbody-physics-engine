#include "ContactGenerator.h"
#include "Collider.h"

#include <stdexcept>

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

	void SphereVsPlane(const SphereCollider& first, const PlaneCollider& second, CollisionData* data)
	{
		//TODO
	}

	void BoxVsBox(const BoxCollider& first, const BoxCollider& second, CollisionData* data)
	{
		// TODO
	}

	void BoxVsPlane(const BoxCollider& first, const PlaneCollider& second, CollisionData* data)
	{
		// TODO
	}

	void PlaneVsPlane(const PlaneCollider& first, const PlaneCollider& second, CollisionData* data)
	{
		// TODO
	}

	void ContactGenerator::DetectContacts(
		const PrimitiveCollider& first,
		const PrimitiveCollider& second,
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
