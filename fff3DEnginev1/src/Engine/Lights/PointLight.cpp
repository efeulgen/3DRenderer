
#include "PointLight.h"

PointLight::PointLight()
{
      Logger::Log("PointLight Constructor");
}

PointLight::PointLight(std::vector<SurfaceShader *> shdrs, int pLightCount)
{
      Logger::Log("PointLight Constructor");

      shaders = shdrs;
      position = glm::vec3(5.0, 5.0, 0.0);
      color = glm::vec3(1.0, 1.0, 1.0);
      intensity = 1.0f;
      pointLightIndex = pLightCount - 1;
}

PointLight::PointLight(std::vector<SurfaceShader *> shdrs, glm::vec3 pos, glm::vec3 col, float i, int pLightCount)
{
      Logger::Log("PointLight Constructor");

      shaders = shdrs;
      position = pos;
      color = col;
      intensity = i;
      pointLightIndex = pLightCount - 1;

      Logger::Log("PointLight Index : ", pointLightIndex);
}

PointLight::~PointLight()
{
      Logger::Log("PointLight Destructor");
}

void PointLight::UseLight()
{
      for (auto shader : shaders)
      {
            if (shader->GetShaderType() == ShaderType::ST_ShadowMapShader)
            {
                  continue;
            }
            glUniform3f(shader->GetPointLightsLocations()[pointLightIndex].uniformPL_position, position[0], position[1], position[2]);
            glUniform3f(shader->GetPointLightsLocations()[pointLightIndex].uniformPL_color, color[0], color[1], color[2]);
            glUniform1f(shader->GetPointLightsLocations()[pointLightIndex].uniformPL_intensity, intensity);
      }
}
