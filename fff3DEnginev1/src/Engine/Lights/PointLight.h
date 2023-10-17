
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "Light.h"
#include "../Shaders/SurfaceShader.h"

class PointLight : public Light
{
private:
      std::vector<SurfaceShader *> shaders;
      glm::vec3 position;
      glm::vec3 color;
      float intensity;

      int pointLightIndex;

public:
      PointLight();
      PointLight(std::vector<SurfaceShader *> shdrs, int pLightCount);
      PointLight(std::vector<SurfaceShader *> shdrs, glm::vec3 pos, glm::vec3 col, float i, int pLightCount);
      ~PointLight();

      void UseLight() override;
};

#endif
