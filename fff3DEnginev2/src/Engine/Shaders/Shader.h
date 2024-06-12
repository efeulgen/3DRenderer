
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include "../Logger/Logger.h"

enum ShaderType
{
      ST_Monochrome,
      ST_Diffuse,
      ST_BlinnPhong
}; // ?

class Shader
{
protected:
      const char *vShaderSrcPath;
      const char *fShaderSrcPath;

      const char *vShaderSrc;
      const char *fShaderSrc;

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
                  Logger::Err("Error compiling shader.");
                  return 0;
            }
            return shader;
      }
      virtual void CreateRenderingProgram() = 0;

      GLuint GetRenderingProgram() const { return renderingProgram; }
      ShaderType GetShaderType() const { return type; }
};

#endif
