
#ifndef SURFACESHADER_H
#define SURFACESHADER_H

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

// *******************************************************************************************************************************************************************************
// *******************************************************************************************************************************************************************************
// *******************************************************************************************************************************************************************************

class SurfaceShader : public Shader
{
protected:
      GLuint uniformModelMatLocation;
      GLuint uniformViewMatLocation;
      GLuint uniformProjectionMatLocation;

      int pointLightCount;
      int spotLightCount;

      GLuint pointLightCountLocation;
      GLuint spotLightCountLocation;

public:
      SurfaceShader() {}
      virtual ~SurfaceShader() {}

      // abstract getters & setters
      virtual GLuint GetUniformLocation(const char *name) const = 0;

      virtual void SetPointLightUniformLocations() = 0;
      virtual void SetSpotLightUniformLocations() = 0;
      virtual void UpdateLightCounts() = 0;
      virtual DirectionalLightLocations GetDirectionalLightUniformLocations() const = 0;
      virtual std::vector<PointLightLocations> GetPointLightsLocations() const = 0;
      virtual std::vector<SpotLightLocations> GetSpotLightsLocations() const = 0;

      void IncrementPointLightCount() { pointLightCount++; }
      void IncrementSpotLightCount() { spotLightCount++; }
};

#endif
