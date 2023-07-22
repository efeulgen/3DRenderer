
#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Logger/Logger.h"

class Shader
{
protected:
      const char *vShaderPath;
      const char *fShaderPath;

      GLuint uniformModelMatLocation;
      GLuint uniformViewMatLocation;
      GLuint uniformProjectionMatLocation;

      GLuint renderingProgram;

public:
      Shader()
      {
            std::cout << "Shader Constructor" << std::endl;
      }
      virtual ~Shader()
      {
            std::cout << "Shader Destructor" << std::endl;
      }

      GLuint CreateShader(const char *shaderSrc, GLenum shaderType)
      {
            GLuint shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &shaderSrc, NULL);
            glCompileShader(shader);

            GLint result = 0;
            GLchar eLog[1024] = {0};
            glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
            if (!result)
            {
                  glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
                  printf("Shader compilation fails: %s \n", eLog);
                  return 0;
            }

            return shader;
      }

      std::string ReadShaderFile(const char *path)
      {
            std::string content;
            std::ifstream fileStream(path, std::ios::in);
            if (!fileStream.is_open())
            {
                  Logger::Err("Failed to read shader file.");
                  return "";
            }

            std::string line = "";
            while (!fileStream.eof())
            {
                  std::getline(fileStream, line);
                  content.append(line + " \n");
            }
            fileStream.close();

            return content;
      }

      void CreateRenderingProgram()
      {
            std::string vShaderSrc_str = ReadShaderFile(vShaderPath);
            std::string fShaderSrc_str = ReadShaderFile(fShaderPath);

            const char *vShaderSrc = vShaderSrc_str.c_str();
            const char *fShaderSrc = fShaderSrc_str.c_str();

            GLuint vShader = CreateShader(vShaderSrc, GL_VERTEX_SHADER);
            GLuint fShader = CreateShader(fShaderSrc, GL_FRAGMENT_SHADER);

            renderingProgram = glCreateProgram();
            glAttachShader(renderingProgram, vShader);
            glAttachShader(renderingProgram, fShader);
            glLinkProgram(renderingProgram);

            GLint result = 0;
            GLchar eLog[1024] = {0};
            glGetProgramiv(renderingProgram, GL_LINK_STATUS, &result);
            if (!result)
            {
                  glGetProgramInfoLog(renderingProgram, sizeof(eLog), NULL, eLog);
                  printf("Error linking renderingProgram: %s \n", eLog);
            }

            SetUniformLocations();
      }

      // abstract getters & setters
      virtual GLuint GetUniformLocation(const char *name) const = 0;
      virtual void SetUniformLocations() = 0;
      // virtual DirectionalLightLocations GetDirectionalLightUniformLocations() const = 0;
      // virtual const PointLightLocations *GetPointLightsLocations() const = 0;
      // virtual const SpotLightLocations *GetSpotLightsLocations() const = 0;

      // getters & setters
      GLuint GetRenderingProgram() const { return renderingProgram; }
};

#endif
