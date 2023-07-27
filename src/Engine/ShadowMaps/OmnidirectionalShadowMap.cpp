
#include "OmnidirectionalShadowMap.h"

OmnidirectionalShadowMap::OmnidirectionalShadowMap(int w, int h)
{
      std::cout << "OmnidirectionalShadowMap Constructor" << std::endl;

      shadowMapWidth = w;
      shadowMapHeight = h;
}

OmnidirectionalShadowMap::~OmnidirectionalShadowMap()
{
      std::cout << "OmnidirectionalShadowMap Destructor" << std::endl;
}

void OmnidirectionalShadowMap::SetBuffers()
{
      // TODO : implement
}
