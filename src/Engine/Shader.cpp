
#include "Shader.h"

Shader::Shader()
{
      std::cout << "Shader Constructor" << std::endl;

      vShaderSrc =
          "#version 330 \n"
          "layout (location = 0) in vec3 pos; \n"
          "layout (location = 1) in vec3 v_in_normal; \n"
          "uniform mat4 model_mat; \n"
          "uniform mat4 projection_mat; \n"
          "out vec3 v_out_normal; \n"
          "out vec3 fragPos; \n"
          "void main() \n"
          "{ \n"
          "gl_Position = projection_mat * model_mat * vec4(pos, 1.0); \n"
          "//v_out_normal = mat3(transpose(inverse(model_mat))) * v_in_normal; \n"
          "v_out_normal = v_in_normal; \n"
          "fragPos = vec3(model_mat * vec4(pos, 1.0)); \n"
          "}";

      fShaderSrc =
          "#version 330 \n"
          "in vec3 v_out_normal; \n"
          "in vec3 fragPos; \n"
          "uniform vec3 lightPos; \n"
          "uniform vec3 lightColor; \n"
          "out vec4 color; \n"
          "void main() \n"
          "{ \n"
          "color = vec4(0.0, 0.0, 0.0, 1.0); \n"
          "vec3 normal = normalize(v_out_normal); \n"
          "vec3 lightDir = normalize(lightPos - fragPos); \n"
          "float diff = max(dot(normal, lightDir), 0.0); \n"
          "vec3 diffuse = diff * lightColor; \n"
          "vec3 vertexColor = vec3(1.0, 1.0, 1.0); \n"
          "color += vec4(vertexColor * diffuse, 1.0); \n"
          "}";
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
