
#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Light.h"
#include "../Shaders/Shader.h"
#include "../Shaders/StandardShader.h"

class DirectionalLight : public Light
{
private:
      glm::vec3 direction;
      glm::vec3 color;
      float directionalIntensity;
      float ambientStrength;

      std::vector<StandardShader *> shaders;

public:
      DirectionalLight();
      DirectionalLight(std::vector<StandardShader *> shdrs);
      DirectionalLight(std::vector<StandardShader *> shdrs, glm::vec3 dir, glm::vec3 col, float dIntensity, float aStrength);
      ~DirectionalLight();

      void UseLight() override;
};

#endif
