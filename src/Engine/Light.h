
#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
private:
      glm::vec3 lightPos;
      glm::vec3 lightColor;

public:
      Light();
      Light(glm::vec3 pos, glm::vec3 color);
      ~Light();

      // getters & setters
      glm::vec3 GetLightPos() { return lightPos; }
      glm::vec3 GetLightColor() { return lightColor; }
};

#endif
