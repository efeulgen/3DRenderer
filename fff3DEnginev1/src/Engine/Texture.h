
#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <GL/glew.h>
#include <stb_image.h>

#include "Logger/Logger.h"

class Texture
{
public:
      Texture();
      ~Texture();

      static GLuint CreateTexture(const char *filePath);
};

#endif
