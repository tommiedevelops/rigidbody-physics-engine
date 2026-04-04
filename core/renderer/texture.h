#pragma once
#include <string>

namespace PhysicsEngine
{
	class Texture
	{
	private:
		unsigned int m_ID;
	public:
		std::string type;
		std::string path;

		Texture(std::string pathToTex);
		unsigned int getID() const;
	};
}
