#pragma once
#include <string>

namespace PhysicsEngine
{
	class Texture
	{
	private:
		unsigned int m_ID;
		std::string m_Name;
	public:
		std::string type;
		std::string path;

		Texture(const std::string pathToTex);
		unsigned int getID() const;

	};
}
