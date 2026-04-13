#pragma once

namespace PhysicsEngine
{
	class Contact;

	namespace ContactResolver
	{
		// This Module has the job of taking in a set of collisions and applying the
		// correct linear and angular impulses to the objects involved as well as 
		// resolving any interpenetration
		
		// Resolves set of contacts for penetration and velocity
		void ResolveContacts(Contact* contacts, unsigned int numContacts, float deltaTime);

		// Prepares contacts for processing by calculating relevant internal data
		void PrepareContactData(Contact* contacts, unsigned int numContacts, float deltaTime);
	};
}
