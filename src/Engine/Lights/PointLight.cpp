
#include "PointLight.h"

PointLight::PointLight()
{
}

PointLight::PointLight(std::vector<Shader *> shdrs)
{
      std::cout << "PointLight Constructor" << std::endl;

      shaders = shdrs;
      position = glm::vec3(5.0, 5.0, 0.0);
      color = glm::vec3(1.0, 1.0, 1.0);
      intensity = 1.0f;
}

PointLight::PointLight(std::vector<Shader *> shdrs, glm::vec3 pos, glm::vec3 col, float i)
{
      std::cout << "PointLight Constructor" << std::endl;

      shaders = shdrs;
      position = pos;
      color = col;
      intensity = i;
}

PointLight::~PointLight()
{
}

void PointLight::UseLight()
{
      for (auto shader : shaders)
      {
            for (auto location : shader->GetPointLightsLocations())
            {
                  glUniform3f(location.uniformPL_position, position[0], position[1], position[2]);
                  glUniform3f(location.uniformPL_color, color[0], color[1], color[2]);
                  glUniform1f(location.uniformPL_intensity, intensity);
            }
      }
}
