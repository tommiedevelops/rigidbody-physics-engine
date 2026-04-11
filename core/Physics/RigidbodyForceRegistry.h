#pragma once

#include <vector>

namespace PhysicsEngine
{
	class RigidbodyComponent;
	class IForceGenerator;

	// Global Registry (relative to Scene) which specifies which
	// forces affect which Rigidbodies
	class RigidbodyForceRegistry
	{
	public:
		void Register(RigidbodyComponent* rb, IForceGenerator* fg);
		void Deregister(RigidbodyComponent* rb, IForceGenerator* fg);
		void ClearAllRegistrations();
		void UpdateForces(float deltaTime);
	private:
		struct RigidbodyForceRegistration
		{
			RigidbodyComponent* rigidbody;
			IForceGenerator*  fg;
		};

		std::vector<RigidbodyForceRegistration> 
		m_Registrations;
	};
}