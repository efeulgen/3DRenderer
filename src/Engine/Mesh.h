
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

#define numVAOs 1
#define numVBOs 1
#define numEBOs 1

struct Transform
{
      glm::vec3 position{glm::vec3{0.0f, 0.0f, 0.0f}};
      double rotation{0.0};
      glm::vec3 scale{glm::vec3{0.0f, 0.0f, 0.0f}};
};

class Mesh
{
private:
      Shader *shader = nullptr;
      GLuint vao[numVAOs];
      GLuint vbo[numVBOs];
      GLuint ebo[numEBOs];

      GLuint uniformModelMatLocation;
      GLuint uniformProjectionMatLocation;

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
      void RenderMesh(glm::mat4 projMat);
      void DestroyMesh();

      // getters & setters
      Shader *GetShader() { return shader; }
};

#endif
