
#include "Shader.h"

Shader::Shader()
{
      std::cout << "Shader Constructor" << std::endl;

      // std::string vShaderSrc_str = ReadShaderFile("./src/Engine/Shaders/DefaultDiffuseShader.vert");
      // std::string fShaderSrc_str = ReadShaderFile("./src/Engine/Shaders/DefaultDiffuseShader.frag");

      // vShaderSrc = vShaderSrc_str.c_str();
      // fShaderSrc = fShaderSrc_str.c_str();

      // *************** for debugging ******************************
      vShaderSrc = "#version 330 \n"
                   "layout (location = 0) in vec3 pos; \n"
                   "layout (location = 1) in vec3 v_in_normal; \n"
                   "layout (location = 2) in vec2 v_in_uv; \n"
                   "uniform mat4 model_mat; \n"
                   "uniform mat4 view_mat; \n"
                   "uniform mat4 projection_mat; \n"
                   "out vec3 v_out_normal; \n"
                   "out vec3 fragPos; \n"
                   "out vec2 v_out_uv; \n"
                   "void main() { \n"
                   "gl_Position = projection_mat * view_mat * model_mat * vec4(pos, 1.0); \n"
                   "v_out_normal = mat3(transpose(inverse(model_mat))) * v_in_normal; \n"
                   "fragPos = vec3(model_mat * vec4(pos, 1.0)); \n"
                   "v_out_uv = v_in_uv;}";

      fShaderSrc = "#version 330 \n"
                   "in vec3 v_out_normal; \n"
                   "in vec3 fragPos; \n"
                   "in vec2 v_out_uv; \n"
                   "uniform vec3 lightPos; \n"
                   "uniform vec3 lightColor; \n"
                   "uniform sampler2D tex; \n"
                   "out vec4 color; \n"
                   "void main() { \n"
                   "vec4 mainTexture = texture(tex, v_out_uv); \n"
                   "vec3 normal = normalize(v_out_normal); \n"
                   "vec3 lightDir = normalize(lightPos - fragPos); \n"
                   "float diffuseFactor = max(dot(normal, lightDir), 0.0); \n"
                   "vec3 diffuse = diffuseFactor * lightColor; \n"
                   "color = mainTexture * vec4(diffuse, 1.0);}";
      // *************** for debugging ******************************
}

Shader::Shader(const char *vSrcPath, const char *fSrcPath)
{
      std::string vShaderSrc_str = ReadShaderFile(vSrcPath);
      std::string fShaderSrc_str = ReadShaderFile(fSrcPath);

      vShaderSrc = vShaderSrc_str.c_str();
      fShaderSrc = fShaderSrc_str.c_str();
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
      // std::cout << vShaderSrc << std::endl; // for debugging
      // std::cout << fShaderSrc << std::endl; // for debugging

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
      std::string shaderStr;
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
            shaderStr.append(line + "\n");
      }
      fileStream.close();

      return shaderStr;
}
