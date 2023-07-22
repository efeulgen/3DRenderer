
#include "StandardShader.h"

StandardShader::StandardShader()
{
      std::cout << "StandardShader Constructor" << std::endl;

      vShaderPath = "./src/Engine/Shaders/ShaderSrc/StandardShader.vert";
      fShaderPath = "./src/Engine/Shaders/ShaderSrc/StandardShader.frag";

      pointLightCount = 0; // for debugging
      spotLightCount = 0;  // for debugging
}

StandardShader::~StandardShader()
{
      std::cout << "StandardShader Destructor" << std::endl;
}

GLuint StandardShader::GetUniformLocation(const char *name) const
{
      if (name == "model")
            return uniformModelMatLocation;
      if (name == "view")
            return uniformViewMatLocation;
      if (name == "proj")
            return uniformProjectionMatLocation;
}

void StandardShader::SetUniformLocations()
{
      uniformModelMatLocation = glGetUniformLocation(renderingProgram, "model_mat");
      uniformViewMatLocation = glGetUniformLocation(renderingProgram, "view_mat");
      uniformProjectionMatLocation = glGetUniformLocation(renderingProgram, "projection_mat");

      // directional light
      dl.uniformDL_direction = glGetUniformLocation(renderingProgram, "directionalLight.DL_direction");
      dl.uniformDL_color = glGetUniformLocation(renderingProgram, "directionalLight.DL_color");
      dl.uniformDL_intensity = glGetUniformLocation(renderingProgram, "directionalLight.DL_intensity");
      dl.uniformAmbientStrength = glGetUniformLocation(renderingProgram, "directionalLight.ambientStrength");

      // point lights
      for (int i = 0; i < pointLightCount; i++)
      {
            char localBuffer[100] = {"\n"};

            snprintf(localBuffer, sizeof(localBuffer), "pointLights[%d].PL_position", i);
            pl[i].uniformPL_position = glGetUniformLocation(renderingProgram, localBuffer);

            snprintf(localBuffer, sizeof(localBuffer), "pointLights[%d].PL_color", i);
            pl[i].uniformPL_color = glGetUniformLocation(renderingProgram, localBuffer);

            snprintf(localBuffer, sizeof(localBuffer), "pointLights[%d].PL_intensity", i);
            pl[i].uniformPL_intensity = glGetUniformLocation(renderingProgram, localBuffer);
      }

      // spot lights
      for (int i = 0; i < spotLightCount; i++)
      {
            char localBuffer[100] = {"\n"};

            snprintf(localBuffer, sizeof(localBuffer), "spotLights[%d].SL_position", i);
            sl[i].uniformSL_position = glGetUniformLocation(renderingProgram, localBuffer);

            snprintf(localBuffer, sizeof(localBuffer), "spotLights[%d].SL_color", i);
            sl[i].uniformSL_color = glGetUniformLocation(renderingProgram, localBuffer);

            snprintf(localBuffer, sizeof(localBuffer), "spotLights[%d].SL_intensity", i);
            sl[i].uniformSL_intensity = glGetUniformLocation(renderingProgram, localBuffer);

            snprintf(localBuffer, sizeof(localBuffer), "spotLights[%d].SL_direction", i);
            sl[i].uniformSL_direction = glGetUniformLocation(renderingProgram, localBuffer);

            snprintf(localBuffer, sizeof(localBuffer), "spotLights[%d].SL_edge", i);
            sl[i].uniformSL_edge = glGetUniformLocation(renderingProgram, localBuffer);
      }
}

DirectionalLightLocations StandardShader::GetDirectionalLightUniformLocations() const
{
      return dl;
}
/*
const PointLightLocations *StandardShader::GetPointLightsLocations() const
{
      return pl;
}

const SpotLightLocations *StandardShader::GetSpotLightsLocations() const
{
      return sl;
}
*/