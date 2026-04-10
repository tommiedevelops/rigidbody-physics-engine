#include "RigidbodyForceRegistry.h"
#include "Rigidbody.h"
#include "IForceGenerator.h"]
#include <iostream>

namespace PhysicsEngine
{
	void RigidbodyForceRegistry::Register(Rigidbody* rb, IForceGenerator* fg)
	{
		if (!rb || !fg) throw std::logic_error("Null rigidbody or force provided");

		m_Registrations.push_back( RigidbodyForceRegistration{rb, fg} );
	}

	void RigidbodyForceRegistry::Deregister(Rigidbody* rb, IForceGenerator* fg)
	{
		if (!rb || !fg) throw std::logic_error("Null rigidbody or force provided");

		for (int i{ 0 }; i < m_Registrations.size(); ++i)
		{
			if (m_Registrations[i].rigidbody == rb && m_Registrations[i].fg == fg)
			{
				// Avoid an O(1) erase() by moving to end and popping
				m_Registrations[i] = std::move(m_Registrations.back());
				m_Registrations.pop_back();
				return;
			}
		}
	}

	void RigidbodyForceRegistry::ClearAllRegistrations()
	{
		m_Registrations.clear();
	}

	void RigidbodyForceRegistry::UpdateForces(float deltaTime)
	{
		for (int i{ 0 }; i < m_Registrations.size(); ++i)
		{

		}
	}

}