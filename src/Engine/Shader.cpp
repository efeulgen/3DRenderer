
#include "Shader.h"

Shader::Shader()
{
      std::cout << "Shader Constructor" << std::endl;

      // default shader
      vShaderPath = "./src/Engine/Shaders/shader.vert";
      fShaderPath = "./src/Engine/Shaders/shader.frag";
}

Shader::Shader(const char *vPath, const char *fPath) : vShaderPath{vPath}, fShaderPath{fPath}
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
            printf("Shader compilation fails: %s \n", eLog);
            return 0;
      }

      return shader;
}

void Shader::CreateRenderingProgram()
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
}

std::string Shader::ReadShaderFile(const char *path)
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
