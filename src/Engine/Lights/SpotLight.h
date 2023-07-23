
#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Light.h"
#include "../Shaders/Shader.h"

class SpotLight : public Light
{
private:
      std::vector<Shader *> shaders;
      glm::vec3 position;
      glm::vec3 color;
      float intensity;
      glm::vec3 direction;
      float edge;

      int spotLightIndex;

public:
      SpotLight();
      SpotLight(std::vector<Shader *> shdrs, int sLightCount);
      SpotLight(std::vector<Shader *> shdrs, glm::vec3 pos, glm::vec3 col, float i, glm::vec3 dir, float e, int sLightCount);
      ~SpotLight();

      void UseLight() override;
};

#endif
