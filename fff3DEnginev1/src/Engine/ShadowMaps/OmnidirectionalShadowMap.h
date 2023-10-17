
#ifndef OMNIDIRECTIONALSHADOWMAP_H
#define OMNIDIRECTIONALSHADOWMAP_H

#include "ShadowMap.h"

class OmnidirectionalShadowMap : public ShadowMap
{
public:
      OmnidirectionalShadowMap(int w, int h);
      ~OmnidirectionalShadowMap();

      void SetBuffers() override;
      GLuint GetShadowMap() override { return shadowMap; }
      GLuint GetShadowBuffer() override { return shadowBuffer; }
};

#endif
