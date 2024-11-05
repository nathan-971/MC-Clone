#include "texture.h"
#include <iostream>

Texture::Texture(const char* path)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int numOfChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &numOfChannels, 0);
    if (data)
    {
        GLenum format; 
        if (numOfChannels == 4)
        {
            format = GL_RGBA;
        }
        else if (numOfChannels == 3)
        {
            format = GL_RGB;
        }
        else
        {
            format = GL_RED;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Successfully Loaded Texture At: \"" << path << "\"" << std::endl;;
    }
    else
    {
        std::cout << "Failed To Load Texture At \"" << path << "\": " << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);
}

void Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
}

SubTexture::SubTexture(Texture* largeTex, float offsetX, float offsetY, float width, float height)
    :texture(largeTex)
{
    float xMin = offsetX / texture->getWidth();
    float yMin = offsetY / texture->getHeight();
    float xMax = (offsetX + width) / texture->getWidth();
    float yMax = (offsetY + height) / texture->getHeight();

    uvCoords[0][0] = xMin; uvCoords[0][1] = yMin; // Bottom-left
    uvCoords[1][0] = xMax; uvCoords[1][1] = yMin; // Bottom-right
    uvCoords[2][0] = xMax; uvCoords[2][1] = yMax; // Top-right
    uvCoords[3][0] = xMin; uvCoords[3][1] = yMax; // Top-left
}