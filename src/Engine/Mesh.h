
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define numVAOs 1
#define numVBOs 1
#define numEBOs 1

class Mesh
{
private:
      GLuint renderingProgram;
      GLuint vao[numVAOs];
      GLuint vbo[numVBOs];
      GLuint ebo[numEBOs];

      GLfloat *vertices;
      unsigned int *indices;

public:
      Mesh();
      Mesh(GLfloat *v, unsigned int *i);
      ~Mesh();

      void SetBuffers();
      void UpdateMesh();
      void RenderMesh();
};

#endif
