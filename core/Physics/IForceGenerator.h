#pragma once

namespace PhysicsEngine
{
	class RigidbodyComponent;

	class ForceGenerator
	{
	public:
		virtual void UpdateForce(RigidbodyComponent* rb, float deltaTime) = 0;
		virtual ~ForceGenerator() = default;
		ForceGenerator() = default;
	};
}