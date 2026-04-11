#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>

#define PRIMITIVE_TYPE(type) PrimitiveType GetType() const override { return PrimitiveType::##type; }

namespace PhysicsEngine
{
	class PrimitiveCollider
	{
	public:
		glm::vec3 localPosition{};
		glm::quat localRotation{};

		enum class PrimitiveType { BOX, SPHERE, CAPSULE, PLANE };

		virtual PrimitiveType GetType() const = 0;
		virtual ~PrimitiveCollider() = default;
	};

	class SphereCollider : public PrimitiveCollider
	{
	public:
		float radius;
		PRIMITIVE_TYPE(SPHERE)
	};

	class BoxCollider : public PrimitiveCollider
	{
	public:
		glm::vec3 halfExtents; // half width/height/depth
		PRIMITIVE_TYPE(BOX)
	};

	class CapsuleCollider : public PrimitiveCollider
	{
	public:
		float radius;
		float halfHeight;
		PRIMITIVE_TYPE(CAPSULE)
	};

	class PlaneCollider : public PrimitiveCollider
	{
	public:
		glm::vec3 normal;
		float offset;
		PRIMITIVE_TYPE(PLANE)
	};

	class Collider
	{
		// Supports composite shape made up of multiple primitives
		std::vector<std::shared_ptr<PrimitiveCollider>> m_Primitives;

		template<typename T, typename... Args>
		T& AddPrimitive(Args&&... args) {
			auto prim = std::make_shared<T>(std::forward<Args>(args)...);
			T& ref = *prim;
			m_Primitives.push_back(std::move(prim));
			return ref;
		}
	};
}