
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Light.h"
#include "Camera.h"

#define numVAOs 1
#define numVBOs 1
#define numEBOs 1
#define numNBOs 1

struct Transform
{
      glm::vec3 position{glm::vec3{0.0f, 0.0f, 0.0f}};
      float rotation{0.0};
      glm::vec3 scale{glm::vec3{0.0f, 0.0f, 0.0f}};
};

class Mesh
{
private:
      Shader *shader = nullptr;
      GLuint vao[numVAOs];
      GLuint vbo[numVBOs];
      GLuint ebo[numEBOs];
      GLuint nbo[numNBOs];

      GLuint uniformModelMatLocation;
      GLuint uniformProjectionMatLocation;
      GLuint uniformLightPosLocation;
      GLuint uniformLightColorLocation;

      GLfloat *vertices = nullptr;
      unsigned int *indices = nullptr;

      Transform transform;

public:
      Mesh();
      Mesh(GLfloat *v, unsigned int *i);
      ~Mesh();

      void SetBuffers();
      void SetShader();
      void UpdateMesh();
      void RenderMesh(Camera *activeCam, std::vector<Light *> lights);
      void DestroyMesh();

      // getters & setters
      Shader *GetShader() { return shader; }
};

#endif
