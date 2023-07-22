
#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
      Light()
      {
            std::cout << "Light Constructor" << std::endl;
      }
      virtual ~Light()
      {
            std::cout << "Light Desturctor" << std::endl;
      }

      virtual void UseLight() = 0;
};

#endif
