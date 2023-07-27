
#include "DirectionalShadowMap.h"

DirectionalShadowMap::DirectionalShadowMap(int w, int h)
{
      std::cout << "DirectionalShadowMap Constructor" << std::endl;

      shadowMapWidth = w;
      shadowMapHeight = h;
}

DirectionalShadowMap::~DirectionalShadowMap()
{
      std::cout << "DirectionalShadowMap Destructor" << std::endl;
}

void DirectionalShadowMap::SetBuffers()
{
      glGenFramebuffers(1, &shadowBuffer);

      glGenTextures(1, &shadowMap);
      glBindTexture(GL_TEXTURE_2D, shadowMap);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
}
