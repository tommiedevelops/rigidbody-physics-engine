#pragma once

namespace PhysicsEngine
{
	class RigidbodyComponent;

	class IForceGenerator
	{
	public:
		virtual void UpdateForce(RigidbodyComponent* rb, float deltaTime) = 0;
		virtual ~IForceGenerator() = default;
	};
}