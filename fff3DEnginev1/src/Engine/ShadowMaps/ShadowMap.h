
#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include <iostream>
#include <GL/glew.h>
#include "../Logger/Logger.h"

class ShadowMap
{
protected:
      GLuint shadowMap;
      GLuint shadowBuffer;
      int shadowMapWidth;
      int shadowMapHeight;

public:
      ShadowMap() {}
      virtual ~ShadowMap() {}

      virtual void SetBuffers() = 0;
      virtual GLuint GetShadowMap() = 0;
      virtual GLuint GetShadowBuffer() = 0;
};

#endif
