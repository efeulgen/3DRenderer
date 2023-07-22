
#ifndef STANDARDSHADER_H
#define STANDARDSHADER_H

#include <iostream>
#include <GL/glew.h>
#include "Shader.h"

struct DirectionalLightLocations
{
      GLuint uniformDL_direction;
      GLuint uniformDL_color;
      GLuint uniformDL_intensity;
      GLuint uniformAmbientStrength;
};

struct PointLightLocations
{
      GLuint uniformPL_position;
      GLuint uniformPL_color;
      GLuint uniformPL_intensity;
};

struct SpotLightLocations
{
      GLuint uniformSL_position;
      GLuint uniformSL_color;
      GLuint uniformSL_intensity;
      GLuint uniformSL_direction;
      GLuint uniformSL_edge;
};

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
      PointLightLocations pl[MAX_POINT_LIGHTS];
      SpotLightLocations sl[MAX_SPOT_LIGHTS];

public:
      StandardShader();
      ~StandardShader();

      // getters & setters
      GLuint GetUniformLocation(const char *name) const override;
      void SetUniformLocations() override;

      DirectionalLightLocations GetDirectionalLightUniformLocations() const;
      // const PointLightLocations *GetPointLightsLocations() const;
      // const SpotLightLocations *GetSpotLightsLocations() const;
};

#endif
