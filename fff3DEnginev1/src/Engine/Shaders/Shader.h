
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

enum ShaderType
{
      ST_SurfaceShader,
      ST_ShadowMapShader
};

class Shader
{
protected:
      const char *vShaderPath;
      const char *fShaderPath;

      GLuint renderingProgram;
      ShaderType type;

public:
      Shader() {}
      virtual ~Shader() {}

      GLuint CreateShader(const char *shaderSrc, GLenum shaderType)
      {
            GLuint shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &shaderSrc, NULL);
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled != 1)
            {
                  int len = 0;
                  char *log;
                  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
                  if (len > 0)
                  {
                        log = (char *)malloc(len);
                        glGetShaderInfoLog(shader, len, nullptr, log);
                        printf("Shader compilation fails: %s \n", log);
                  }
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

            GLint isLinked = 0;
            glGetProgramiv(renderingProgram, GL_LINK_STATUS, &isLinked);
            if (isLinked != 1)
            {
                  int len = 0;
                  char *log;
                  glGetProgramiv(renderingProgram, GL_INFO_LOG_LENGTH, &len);
                  if (len > 0)
                  {
                        log = (char *)malloc(len);
                        glGetProgramInfoLog(renderingProgram, len, nullptr, log);
                        printf("Error linking renderingProgram: %s \n", log);
                  }
            }

            SetUniformLocations();
      }

      void DetroyShader() { delete this; }

      virtual void SetUniformLocations() = 0;

      // getters & setters
      GLuint GetRenderingProgram() const { return renderingProgram; }
      ShaderType GetShaderType() { return type; }
};

#endif
