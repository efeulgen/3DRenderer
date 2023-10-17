
#ifndef DIRECTIONALSHADOWMAP_H
#define DIRECTIONALSHADOWMAP_H

#include "ShadowMap.h"

class DirectionalShadowMap : public ShadowMap
{
public:
      DirectionalShadowMap(int w, int h);
      ~DirectionalShadowMap();

      void SetBuffers() override;
      GLuint GetShadowMap() override { return shadowMap; }
      GLuint GetShadowBuffer() override { return shadowBuffer; }
};

#endif
