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

		Texture(std::string pathToTex, std::string textureName);
		unsigned int getID() const;

		std::string& GetName()
		{
			return m_Name;
		}

	};
}
