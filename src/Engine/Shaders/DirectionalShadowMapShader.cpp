
#include "DirectionalShadowMapShader.h"

DirectionalShadowMapShader::DirectionalShadowMapShader()
{
      Logger::Log("DirectionalShadowMapShader Constructor");

      vShaderPath = "./src/Engine/Shaders/ShaderSrc/DirectionalShadowMapShader.vert";
      fShaderPath = "./src/Engine/Shaders/ShaderSrc/DirectionalShadowMapShader.frag";

      type = ShaderType::ST_ShadowMapShader;
}

DirectionalShadowMapShader::~DirectionalShadowMapShader()
{
      Logger::Log("DirectionalShadowMapShader Destructor");
}

void DirectionalShadowMapShader::SetUniformLocations()
{
      uniformDirectionalLightTransformLocation = glGetUniformLocation(renderingProgram, "directional_light_transform");
      uniformModelMatLocation = glGetUniformLocation(renderingProgram, "model_mat");
}
