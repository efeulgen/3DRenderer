
#include "OmnidirectionalShadowMap.h"

OmnidirectionalShadowMap::OmnidirectionalShadowMap(int w, int h)
{
      Logger::Log("OmnidirectionalShadowMap Constructor");

      shadowMapWidth = w;
      shadowMapHeight = h;
}

OmnidirectionalShadowMap::~OmnidirectionalShadowMap()
{
      Logger::Log("OmnidirectionalShadowMap Destructor");
}

void OmnidirectionalShadowMap::SetBuffers()
{
      // TODO : implement
}
