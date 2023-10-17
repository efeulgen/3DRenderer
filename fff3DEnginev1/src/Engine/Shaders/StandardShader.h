
#ifndef STANDARDSHADER_H
#define STANDARDSHADER_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "SurfaceShader.h"

const int MAX_POINT_LIGHTS = 20;
const int MAX_SPOT_LIGHTS = 20;

class StandardShader : public SurfaceShader
{
private:
      // materila properties -> TODO : implement
      // glm::vec3 baseColor;
      // float metallic;
      // float roughness;
      // float specular;

      DirectionalLightLocations dl;
      std::vector<PointLightLocations> pl;
      std::vector<SpotLightLocations> sl;

public:
      StandardShader(int pLightCount, int sLightCount);
      ~StandardShader();

      // getters & setters
      GLuint GetUniformLocation(const char *name) const override;
      void SetUniformLocations() override;
      void SetPointLightUniformLocations() override;
      void SetSpotLightUniformLocations() override;
      void UpdateLightCounts() override;

      DirectionalLightLocations GetDirectionalLightUniformLocations() const override;
      std::vector<PointLightLocations> GetPointLightsLocations() const override;
      std::vector<SpotLightLocations> GetSpotLightsLocations() const override;
};

#endif
