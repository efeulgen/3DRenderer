
#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
private:
      const char *vShaderSrc;
      const char *fShaderSrc;

      GLuint renderingProgram;

public:
      Shader();
      Shader(const char *vSrc, const char *fSrc);
      ~Shader();

      GLuint CreateShader(const char *shaderSrc, GLenum shaderType);
      void CreateRenderingProgram();
      GLuint GetRenderingProgram() { return renderingProgram; }
};

#endif
