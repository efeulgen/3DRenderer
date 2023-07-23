
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
      std::cout << "Directional Light Constructor" << std::endl;
}

DirectionalLight::DirectionalLight(std::vector<Shader *> shdrs)
{
      std::cout << "Directional Light Constructor" << std::endl;

      shaders = shdrs;
      direction = glm::vec3(0.5, -1.0, 0.0);
      color = glm::vec3(1.0, 1.0, 1.0);
      directionalIntensity = 1.0f;
      ambientStrength = 0.1;
}

DirectionalLight::DirectionalLight(std::vector<Shader *> shdrs, glm::vec3 dir, glm::vec3 col, float dIntensity, float aStrength) : shaders{shdrs}, direction{dir}, color{col}, directionalIntensity{dIntensity}, ambientStrength{aStrength}
{
      std::cout << "Directional Light Constructor" << std::endl;
}

DirectionalLight::~DirectionalLight()
{
      std::cout << "Directional Light Destructor" << std::endl;
}

void DirectionalLight::UseLight()
{
      for (auto shader : shaders)
      {
            glUniform3f(shader->GetDirectionalLightUniformLocations().uniformDL_direction, direction[0], direction[1], direction[2]);
            glUniform3f(shader->GetDirectionalLightUniformLocations().uniformDL_color, color[0], color[1], color[2]);
            glUniform1f(shader->GetDirectionalLightUniformLocations().uniformDL_intensity, directionalIntensity);
            glUniform1f(shader->GetDirectionalLightUniformLocations().uniformAmbientStrength, ambientStrength);
      }
}
