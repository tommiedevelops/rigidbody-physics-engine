#pragma once

namespace PhysicsEngine
{
	class Contact;

	namespace ContactResolver
	{
		// Resolves set of contacts for penetration and velocity
		void ResolveContacts(Contact* contacts, unsigned int numContacts, float deltaTime);

		// Prepares contacts for processing by calculating relevant internal data
		void PrepareContactData(Contact* contacts, unsigned int numContacts, float deltaTime);
	};
}
