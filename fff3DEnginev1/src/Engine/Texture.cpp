
#include "Texture.h"

Texture::Texture()
{
      Logger::Log("Texture Constructor");
}

Texture::~Texture()
{
      Logger::Log("Texture Destructor");
}

GLuint Texture::CreateTexture(const char *filePath)
{
      GLuint textureID;
      int width, height, bitDepth;
      unsigned char *textureData = stbi_load(filePath, &width, &height, &bitDepth, 0);
      if (!textureData)
      {
            Logger::Err("Error loading texture.");
      }

      glGenTextures(1, &textureID);
      glBindTexture(GL_TEXTURE_2D, textureID);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
      glGenerateMipmap(GL_TEXTURE_2D);

      glBindTexture(GL_TEXTURE_2D, 0);
      stbi_image_free(textureData);

      return textureID;
}
