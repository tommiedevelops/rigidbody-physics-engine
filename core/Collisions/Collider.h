#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

	public:
		glm::mat4 GetOffset() const
		{
			glm::mat4 T{ glm::translate(glm::mat4(1.0f), localPosition) };
			glm::mat4 R{ glm::toMat4(localRotation) };
			return T * R;
		}
	};

	class SphereCollider : public PrimitiveCollider
	{
	public:
		float m_Radius;
		PRIMITIVE_TYPE(SPHERE)
		SphereCollider(float radius) : m_Radius{ radius } {}
	};

	class BoxCollider : public PrimitiveCollider
	{
	public:
		glm::vec3 m_HalfExtents; // half width/height/depth
		PRIMITIVE_TYPE(BOX)

		BoxCollider(glm::vec3 halfExtents) : m_HalfExtents{ halfExtents } {}
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
		glm::vec3 m_Normal;
		float m_PlaneOffset;
		PRIMITIVE_TYPE(PLANE)
		PlaneCollider(glm::vec3 normal, float planeOffset) : m_Normal{ normal }, m_PlaneOffset{ planeOffset } {}
	};

	struct ColliderComponent
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