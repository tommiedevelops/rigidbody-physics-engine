#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
private:
	unsigned int m_ID;
public:
	std::string type;
	std::string path;

	Texture(const char* pathToTexture);
	unsigned int getID() const;
};

#endif