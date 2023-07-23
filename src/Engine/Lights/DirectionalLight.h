
#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Light.h"
#include "../Shaders/Shader.h"

class DirectionalLight : public Light
{
private:
      std::vector<Shader *> shaders;

      glm::vec3 direction;
      glm::vec3 color;
      float directionalIntensity;
      float ambientStrength;

public:
      DirectionalLight();
      DirectionalLight(std::vector<Shader *> shdrs);
      DirectionalLight(std::vector<Shader *> shdrs, glm::vec3 dir, glm::vec3 col, float dIntensity, float aStrength);
      ~DirectionalLight();

      void UseLight() override;
};

#endif
