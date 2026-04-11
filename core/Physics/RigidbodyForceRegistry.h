#pragma once

#include <vector>

namespace PhysicsEngine
{
	class RigidbodyComponent;
	class ForceGenerator;

	// Global Registry (relative to Scene) which specifies which
	// forces affect which Rigidbodies
	class RigidbodyForceRegistry
	{
	public:
		void Register(RigidbodyComponent* rb, ForceGenerator* fg);
		void Deregister(RigidbodyComponent* rb, ForceGenerator* fg);
		void ClearAllRegistrations();
		void UpdateForces(float deltaTime);
	private:
		struct RigidbodyForceRegistration
		{
			RigidbodyComponent* rigidbody;
			ForceGenerator*  fg;
		};

		std::vector<RigidbodyForceRegistration> 
		m_Registrations;
	};
}