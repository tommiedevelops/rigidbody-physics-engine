#include "GravityForceGenerator.h"
#include "Rigidbody.h"

namespace PhysicsEngine
{
	void GravityForceGenerator::UpdateForce(RigidbodyComponent* rb, float deltaTime) 
	{
		// Don't affect objects with infinite mass
		if (!rb->HasFiniteMass()) return;

		rb->AddLinearForce(m_Gravity * rb->GetMass());
	}

}
