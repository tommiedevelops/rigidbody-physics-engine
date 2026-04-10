#pragma once

namespace PhysicsEngine
{
	class Rigidbody;

	class IForceGenerator
	{
	public:
		virtual void UpdateForce(Rigidbody* rb, float deltaTime) = 0;
		virtual ~IForceGenerator() = default;
	};
}