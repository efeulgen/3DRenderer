
#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Logger/Logger.h"

class Shader
{
private:
      const char *vShaderPath;
      const char *fShaderPath;

      GLuint renderingProgram;

protected:
      // ******************** to be implemented ********************
      // glm::vec3 baseColor;
      // float metallic;
      // float roughness;
      // float specular;

public:
      Shader();
      Shader(const char *vSrcPath, const char *fSrcPath);
      ~Shader();

      GLuint CreateShader(const char *shaderSrc, GLenum shaderType);
      void CreateRenderingProgram();
      std::string ReadShaderFile(const char *path);

      // getters & setters
      GLuint GetRenderingProgram() { return renderingProgram; }
};

#endif
