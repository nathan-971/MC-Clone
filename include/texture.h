#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "stb/stb_image.h"
#include "glad/glad.h"

class Texture
{
public:
	Texture(const char* path);
	void Bind() const;
	int getHeight() const { return height; };
	int getWidth() const { return width; };
private:
	int height, width;
	GLuint ID;
};

struct SubTexture
{
	Texture* texture;
	float uvCoords[4][2];
	SubTexture(Texture* largeTex, float offsetX, float offsetY, float width, float height);
	void Bind() const { texture->Bind(); };
};

#endif