
#ifndef DIRECTIONALSHADOWMAPSHADER_H
#define DIRECTIONALSHADOWMAPSHADER_H

#include <glm/glm.hpp>
#include "Shader.h"

class DirectionalShadowMapShader : public Shader
{
private:
      GLuint uniformDirectionalLightTransformLocation;
      GLuint uniformModelMatLocation;

public:
      DirectionalShadowMapShader();
      ~DirectionalShadowMapShader();

      void SetUniformLocations() override;

      GLuint GetUniformDirectionalLightTransformLocation() { return uniformDirectionalLightTransformLocation; }
      GLuint GetUniformModelMatLocation() { return uniformModelMatLocation; }
};

#endif
