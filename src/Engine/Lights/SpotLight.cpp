
#include "SpotLight.h"

SpotLight::SpotLight()
{
}

SpotLight::SpotLight(std::vector<Shader *> shdrs)
{
      shaders = shdrs;
      position = glm::vec3(5.0, 0.0, 0.0);
      color = glm::vec3(1.0, 1.0, 1.0);
      intensity = 1.0;
      direction = glm::vec3(0.0, -1.0, 0.0);
      edge = 25.0f;
}

SpotLight::SpotLight(std::vector<Shader *> shdrs, glm::vec3 pos, glm::vec3 col, float i, glm::vec3 dir, float e)
{
      shaders = shdrs;
      position = pos;
      color = col;
      intensity = i;
      direction = dir;
      edge = e;
}

SpotLight::~SpotLight()
{
}

void SpotLight::UseLight()
{
}
