
#include "StandardShader.h"

StandardShader::StandardShader(int pLightCount, int sLightCount)
{
      Logger::Log("StandardShader Constructor");

      vShaderPath = "./src/Engine/Shaders/ShaderSrc/StandardShader.vert";
      fShaderPath = "./src/Engine/Shaders/ShaderSrc/StandardShader.frag";

      pointLightCount = pLightCount;
      spotLightCount = sLightCount;

      type = ShaderType::ST_SurfaceShader;
}

StandardShader::~StandardShader()
{
      Logger::Log("StandardShader Destructor");
}

GLuint StandardShader::GetUniformLocation(const char *name) const
{
      std::string nameStr(name);
      if (nameStr == "model")
      {
            return uniformModelMatLocation;
      }
      if (nameStr == "view")
      {
            return uniformViewMatLocation;
      }
      if (nameStr == "proj")
      {
            return uniformProjectionMatLocation;
      }
      return -1;
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

      // light counts
      pointLightCountLocation = glGetUniformLocation(renderingProgram, "pointLightCount");
      spotLightCountLocation = glGetUniformLocation(renderingProgram, "spotLightCount");

      // point lights
      SetPointLightUniformLocations();

      // spot lights
      SetSpotLightUniformLocations();

      // textures
      texLocation = glGetUniformLocation(renderingProgram, "tex");
      shadowMapLocation = glGetUniformLocation(renderingProgram, "directionalShadowMap");
}
void StandardShader::SetPointLightUniformLocations()
{
      if (!pl.empty())
      {
            pl.clear();
      }
      for (int i = 0; i < pointLightCount; i++)
      {
            PointLightLocations newPL;
            pl.push_back(newPL);

            char localBuffer[100] = {"\n"};

            snprintf(localBuffer, sizeof(localBuffer), "pointLights[%d].PL_position", i);
            pl[i].uniformPL_position = glGetUniformLocation(renderingProgram, localBuffer);

            snprintf(localBuffer, sizeof(localBuffer), "pointLights[%d].PL_color", i);
            pl[i].uniformPL_color = glGetUniformLocation(renderingProgram, localBuffer);

            snprintf(localBuffer, sizeof(localBuffer), "pointLights[%d].PL_intensity", i);
            pl[i].uniformPL_intensity = glGetUniformLocation(renderingProgram, localBuffer);
      }
}

void StandardShader::SetSpotLightUniformLocations()
{
      if (!sl.empty())
      {
            sl.clear();
      }
      for (int i = 0; i < spotLightCount; i++)
      {
            SpotLightLocations newSL;
            sl.push_back(newSL);

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

void StandardShader::UpdateLightCounts()
{
      glUniform1i(pointLightCountLocation, pointLightCount);
      glUniform1i(spotLightCountLocation, spotLightCount);
}

DirectionalLightLocations StandardShader::GetDirectionalLightUniformLocations() const
{
      return dl;
}

std::vector<PointLightLocations> StandardShader::GetPointLightsLocations() const
{
      return pl;
}

std::vector<SpotLightLocations> StandardShader::GetSpotLightsLocations() const
{
      return sl;
}
