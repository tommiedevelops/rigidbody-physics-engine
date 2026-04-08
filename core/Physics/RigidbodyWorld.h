#pragma once

#include "Rigidbody.h"

namespace PhysicsEngine
{
	class RigidbodyRegistration {};

	class RigidbodyWorld
	{
		RigidbodyRegistration registration;

		Rigidbody* firstRb;
	};
}