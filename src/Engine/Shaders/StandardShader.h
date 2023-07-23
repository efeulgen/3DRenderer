
#ifndef STANDARDSHADER_H
#define STANDARDSHADER_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "Shader.h"

const int MAX_POINT_LIGHTS = 20;
const int MAX_SPOT_LIGHTS = 20;

class StandardShader : public Shader
{
private:
      int pointLightCount;
      int spotLightCount;

      // materila properties -> TODO : implement
      // glm::vec3 baseColor;
      // float metallic;
      // float roughness;
      // float specular;

      DirectionalLightLocations dl;
      // PointLightLocations pl[MAX_POINT_LIGHTS];
      // SpotLightLocations sl[MAX_SPOT_LIGHTS];
      std::vector<PointLightLocations> pl;
      std::vector<SpotLightLocations> sl;

public:
      StandardShader();
      ~StandardShader();

      // getters & setters
      GLuint GetUniformLocation(const char *name) const override;
      void SetUniformLocations() override;

      DirectionalLightLocations GetDirectionalLightUniformLocations() const override;
      // const PointLightLocations *GetPointLightsLocations() const override;
      // const SpotLightLocations *GetSpotLightsLocations() const override;
      std::vector<PointLightLocations> GetPointLightsLocations() const override;
      std::vector<SpotLightLocations> GetSpotLightsLocations() const override;
};

#endif
