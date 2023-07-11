
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#define numVAOs 1
#define numVBOs 1
#define numEBOs 1

class Mesh
{
private:
      // GLuint renderingProgram;
      Shader *shader = nullptr;
      GLuint vao[numVAOs];
      GLuint vbo[numVBOs];
      GLuint ebo[numEBOs];

      GLfloat *vertices = nullptr;
      unsigned int *indices = nullptr;

public:
      Mesh();
      Mesh(GLfloat *v, unsigned int *i);
      ~Mesh();

      void SetBuffers();
      void UpdateMesh();
      void RenderMesh();
      void DestroyMesh();
};

#endif
