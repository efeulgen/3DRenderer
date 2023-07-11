
#include "Shader.h"

Shader::Shader()
{
      std::cout << "Shader Constructor" << std::endl;

      vShaderSrc =
          "#version 330 \n"
          "layout (location = 0) in vec3 pos; \n"
          "uniform mat4 model_mat; \n"
          "uniform mat4 projection_mat; \n"
          "void main() \n"
          "{ gl_Position = projection_mat * model_mat * vec4(pos, 1.0); }";

      fShaderSrc =
          "#version 330 \n"
          "out vec4 color; \n"
          "void main() \n"
          "{ color = vec4(1.0, 0.0, 0.0, 1.0); }";
}

Shader::Shader(const char *vSrc, const char *fSrc) : vShaderSrc{vSrc}, fShaderSrc{fSrc}
{
}

Shader::~Shader()
{
      std::cout << "Shader Destructor" << std::endl;
}

GLuint Shader::CreateShader(const char *shaderSrc, GLenum shaderType)
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
            printf("Shader compilation fails: %s", eLog);
            return 0;
      }

      return shader;
}

void Shader::CreateRenderingProgram()
{
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
            printf("Error linking renderingProgram: %s", eLog);
      }
}
