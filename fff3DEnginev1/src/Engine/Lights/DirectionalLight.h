
#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Light.h"
#include "../Shaders/SurfaceShader.h"

class DirectionalLight : public Light
{
private:
      std::vector<SurfaceShader *> shaders;

      glm::vec3 direction;
      glm::vec3 color;
      float directionalIntensity;
      float ambientStrength;

      glm::mat4 lightProjection;

public:
      DirectionalLight();
      DirectionalLight(std::vector<SurfaceShader *> shdrs);
      DirectionalLight(std::vector<SurfaceShader *> shdrs, glm::vec3 dir, glm::vec3 col, float dIntensity, float aStrength);
      ~DirectionalLight();

      void UseLight() override;

      glm::mat4 GetLightTransform();
};

#endif
