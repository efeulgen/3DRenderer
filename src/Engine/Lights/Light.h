
#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Logger/Logger.h"

class Light
{
public:
      Light()
      {
            Logger::Log("Light Constructor");
      }
      virtual ~Light()
      {
            Logger::Log("Light Destructor");
      }
      virtual void UseLight() = 0;
};

#endif
