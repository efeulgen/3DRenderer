
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
      Logger::Log("DirectionalLight Constructor");

      lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

DirectionalLight::DirectionalLight(std::vector<SurfaceShader *> shdrs)
{
      Logger::Log("DirectionalLight Constructor");

      shaders = shdrs;
      direction = glm::vec3(0.5, -1.0, 0.0);
      color = glm::vec3(1.0, 1.0, 1.0);
      directionalIntensity = 1.0f;
      ambientStrength = 0.1;

      lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

DirectionalLight::DirectionalLight(std::vector<SurfaceShader *> shdrs, glm::vec3 dir, glm::vec3 col, float dIntensity, float aStrength) : shaders{shdrs}, direction{dir}, color{col}, directionalIntensity{dIntensity}, ambientStrength{aStrength}
{
      Logger::Log("DirectionalLight Constructor");
}

DirectionalLight::~DirectionalLight()
{
      Logger::Log("DirectionalLight Destructor");
}

void DirectionalLight::UseLight()
{
      for (auto shader : shaders)
      {
            if (shader->GetShaderType() == ShaderType::ST_ShadowMapShader)
            {
                  continue;
            }
            glUniform3f(shader->GetDirectionalLightUniformLocations().uniformDL_direction, direction[0], direction[1], direction[2]);
            glUniform3f(shader->GetDirectionalLightUniformLocations().uniformDL_color, color[0], color[1], color[2]);
            glUniform1f(shader->GetDirectionalLightUniformLocations().uniformDL_intensity, directionalIntensity);
            glUniform1f(shader->GetDirectionalLightUniformLocations().uniformAmbientStrength, ambientStrength);
      }
}

glm::mat4 DirectionalLight::GetLightTransform()
{
      return lightProjection * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
