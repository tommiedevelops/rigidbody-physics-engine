#include "ContactResolver.h"
#include "ContactGenerator.h"
#include "Rigidbody.h"

namespace PhysicsEngine
{
	static void ConstructOrthonormalBasis(const glm::vec3& x, glm::vec3* y, glm::vec3* z)
	{
		*z = glm::normalize(glm::cross(x, *y));

		// check if x and y are parallel
		if (glm::length2(*z) == 0.0f) return; 

		(*y) = glm::normalize(glm::cross(*z, x));
	}

	void ContactResolver::ResolveContacts(Contact* contacts, unsigned int numContacts, float deltaTime)
	{
		for (auto i{ 0 }; i < numContacts; ++i)
		{
			const auto contactNormal{ glm::normalize(contacts[i].normal) };
			const auto contactPoint{ contacts[i].point };
			const auto restitution{ contacts[i].restitution };

			RigidbodyComponent* bodyA{ contacts[i].bodyA };
			RigidbodyComponent* bodyB{ contacts[i].bodyB };

			glm::vec3 rA{ bodyA ? contactPoint - bodyA->m_LinearPosition : glm::vec3(0) };
			glm::vec3 rB{ bodyB ? contactPoint - bodyB->m_LinearPosition : glm::vec3(0) };

			auto vPointA = bodyA ? bodyA->m_LinearVelocity + glm::cross(bodyA->m_AngularVelocity, rA) : glm::vec3(0);
			auto vPointB = bodyB ? bodyB->m_LinearVelocity + glm::cross(bodyB->m_AngularVelocity, rB) : glm::vec3(0);

			auto relativeVelocity = vPointB - vPointA;

			auto separatingVelocity = glm::dot(relativeVelocity, contactNormal);

			if (separatingVelocity > 0)
				continue; // no work to do

			float newSeparatingVelocity = -restitution * separatingVelocity;

			if (fabsf(separatingVelocity) < 0.01f)
				newSeparatingVelocity = 0.0f;

			float deltaVelocity = newSeparatingVelocity - separatingVelocity;

			float totalInverseMass = 0.0f;

			if (bodyA) totalInverseMass += bodyA->m_InverseMass;
			if (bodyB) totalInverseMass += bodyB->m_InverseMass;

			float angularEffect = 0.0f;

			if (bodyA)
			{
				auto impulsiveTorqueA{ glm::cross(rA, contactNormal) };
				auto deltaAngVelPerUnitImpulseA{ bodyA->m_InverseInertiaTensorWorldSpace * impulsiveTorqueA };
				auto deltaLinVelPerUnitImpulseA{ glm::cross(deltaAngVelPerUnitImpulseA, rA) };
				float angularEffectA{ glm::dot(deltaLinVelPerUnitImpulseA, contactNormal) };
				angularEffect += angularEffectA;
			}

			if (bodyB)
			{
				auto impulsiveTorqueB{ glm::cross(rB, contactNormal) };
				auto deltaAngVelPerUnitImpulseB{ bodyB->m_InverseInertiaTensorWorldSpace * impulsiveTorqueB };
				auto deltaLinVelPerUnitImpulseB{ glm::cross(deltaAngVelPerUnitImpulseB, rB) };
				float angularEffectB{ glm::dot(deltaLinVelPerUnitImpulseB, contactNormal) };
				angularEffect += angularEffectB;
			}

			float denominator{ totalInverseMass + angularEffect };

			if (denominator <= 0)
				continue;

			float impulseMagnitude = deltaVelocity / denominator;
			glm::vec3 impulse = impulseMagnitude * contactNormal;

			if (bodyA)
			{
				bodyA->m_LinearVelocity -= impulse * bodyA->m_InverseMass;
				bodyA->m_AngularVelocity -= bodyA->m_InverseInertiaTensorWorldSpace * glm::cross(rA, impulse);
			}

			if (bodyB)
			{
				bodyB->m_AngularVelocity += bodyB->m_InverseInertiaTensorWorldSpace * glm::cross(rB, impulse);
				bodyB->m_LinearVelocity += impulse * bodyB->m_InverseMass;
			}
		}
	}

	void ContactResolver::ResolveInterpenetration(Contact* contacts, unsigned int numContacts, float deltaTime)
	{
		for (unsigned int i = 0; i < numContacts; ++i)
		{
			Contact& contact = contacts[i];

			glm::vec3 normal = glm::normalize(contact.normal);
			float penetration = contact.penetration;

			if (penetration <= 0.0f)
				continue;

			RigidbodyComponent* bodyA = contact.bodyA;
			RigidbodyComponent* bodyB = contact.bodyB;

			float invMassA = bodyA ? bodyA->m_InverseMass : 0.0f;
			float invMassB = bodyB ? bodyB->m_InverseMass : 0.0f;

			float totalInverseMass = invMassA + invMassB;

			if (totalInverseMass <= 0.0f)
				continue;

			glm::vec3 correction = normal * penetration;

			if (bodyA)
			{
				bodyA->m_LinearPosition -= correction * (invMassA / totalInverseMass);
			}

			if (bodyB)
			{
				bodyB->m_LinearPosition += correction * (invMassB / totalInverseMass);
			}
		}
	}

}