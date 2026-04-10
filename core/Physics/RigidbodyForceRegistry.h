#pragma once

#include <vector>

namespace PhysicsEngine
{
	class Rigidbody;
	class IForceGenerator;

	// Global Registry (relative to Scene) which specifies which
	// forces affect which Rigidbodies
	class RigidbodyForceRegistry
	{
	public:
		void Register(Rigidbody* rb, IForceGenerator* fg);
		void Deregister(Rigidbody* rb, IForceGenerator* fg);
		void ClearAllRegistrations();
		void UpdateForces(float deltaTime);
	private:
		struct RigidbodyForceRegistration
		{
			Rigidbody* rigidbody;
			IForceGenerator*  fg;
		};

		std::vector<RigidbodyForceRegistration> 
		m_Registrations;
	};
}