
#include "SpotLight.h"

SpotLight::SpotLight()
{
      Logger::Log("SpotLight Constructor");
}

SpotLight::SpotLight(std::vector<SurfaceShader *> shdrs, int sLightCount)
{
      Logger::Log("SpotLight Constructor");

      shaders = shdrs;
      position = glm::vec3(5.0, 0.0, 0.0);
      color = glm::vec3(1.0, 1.0, 1.0);
      intensity = 1.0;
      direction = glm::vec3(0.0, -1.0, 0.0);
      edge = 25.0f;

      spotLightIndex = sLightCount - 1;
}

SpotLight::SpotLight(std::vector<SurfaceShader *> shdrs, glm::vec3 pos, glm::vec3 col, float i, glm::vec3 dir, float e, int sLightCount)
{
      Logger::Log("SpotLight Constructor");

      shaders = shdrs;
      position = pos;
      color = col;
      intensity = i;
      direction = dir;
      edge = e;

      spotLightIndex = sLightCount - 1;
}

SpotLight::~SpotLight()
{
      Logger::Log("SpotLight Destructor");
}

void SpotLight::UseLight()
{
      for (auto shader : shaders)
      {
            if (shader->GetShaderType() == ShaderType::ST_ShadowMapShader)
            {
                  continue;
            }
            glUniform3f(shader->GetSpotLightsLocations()[spotLightIndex].uniformSL_position, position[0], position[1], position[2]);
            glUniform3f(shader->GetSpotLightsLocations()[spotLightIndex].uniformSL_color, color[0], color[1], color[2]);
            glUniform1f(shader->GetSpotLightsLocations()[spotLightIndex].uniformSL_intensity, intensity);
            glUniform3f(shader->GetSpotLightsLocations()[spotLightIndex].uniformSL_direction, direction[0], direction[1], direction[2]);
            glUniform1f(shader->GetSpotLightsLocations()[spotLightIndex].uniformSL_edge, edge);
      }
}
