#include "ContactResolver.h"
#include "ContactGenerator.h"

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

			// Construct matrix to transform world space points to contact space where the contact normal is +y
			const auto contactNormal{ glm::normalize(contacts[i].normal) };

			const glm::vec3 X_AXIS(1, 0, 0);
			const glm::vec3 Y_AXIS(0, 1, 0);
			
			// If statement added for extra stability
			glm::vec3 contactZAxis, contactYAxis;
			if ( fabsf(glm::dot(X_AXIS, contactNormal)) > fabsf(glm::dot(Y_AXIS, contactNormal)) )
			{ // normal is closer to the x-axis than y-axis
				contactYAxis = Y_AXIS;
				ConstructOrthonormalBasis(contactNormal, &contactYAxis, &contactZAxis);
			}
			else
			{
				contactYAxis = X_AXIS;
				ConstructOrthonormalBasis(contactNormal, &contactYAxis, &contactZAxis);
			}

			glm::mat3 contactBasis{ contactNormal, contactYAxis, contactZAxis };
			glm::mat3 inverseContactBasis{ glm::transpose(contactBasis) };

		}
	}

	// Prepares contacts for processing by calculating relevant internal data
	void ContactResolver::PrepareContactData(Contact* contacts, unsigned int numContacts, float deltaTime)
	{
		//TODO
	}

}