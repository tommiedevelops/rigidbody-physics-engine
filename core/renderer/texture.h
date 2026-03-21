#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
private:
	unsigned int m_ID;
public:
	Texture(const char* pathToTexture);

	unsigned int getID() const;
};

#endif