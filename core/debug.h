#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace PhysicsEngine
{
	inline std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
		return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	}
	inline std::ostream& operator<<(std::ostream& os, const glm::quat& q) {
		return os << "(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
	}
}

