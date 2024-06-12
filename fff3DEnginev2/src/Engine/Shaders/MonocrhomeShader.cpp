
#include "MonochromeShader.h"

MonochromeShader::MonochromeShader()
{
      Logger::Log("MonochromeShader Constructor");

      vShaderSrc = "#version 330 \n"
                   "layout(location = 0) in vec3 pos; \n"
                   "void main() \n"
                   "{ gl_Position = vec4(pos, 1.0); }";

      fShaderSrc = "#version 330 \n"
                   "out vec4 color; \n"
                   "void main() \n"
                   "{ color = vec4(1.0, 1.0, 0.0, 1.0); }";
}

MonochromeShader::~MonochromeShader()
{
      Logger::Log("MonochromeShader Destructor");
}

void MonochromeShader::CreateRenderingProgram()
{
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
}
