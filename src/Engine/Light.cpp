
#include "Light.h"

Light::Light()
{
      std::cout << "Light Constructor" << std::endl;

      lightPos = glm::vec3(0.0f, 5.0f, 0.0f);
      lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

Light::Light(glm::vec3 pos, glm::vec3 color) : lightPos{pos}, lightColor{color}
{
}

Light::~Light()
{
      std::cout << "Light Destructor" << std::endl;
}
