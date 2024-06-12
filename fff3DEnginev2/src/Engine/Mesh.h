
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include "Logger/Logger.h"
#include "Shaders/MonochromeShader.h"

#define numVAOs 1
#define numVBOs 1
#define numEBOs 1
#define numNBOs 1

class Mesh
{
protected:
      int meshID;
      const char *tag;

      // buffers
      GLuint vao[numVAOs];
      GLuint vbo[numVBOs];
      GLuint ebo[numEBOs];

      GLfloat *vertices;
      unsigned int *indices;
      unsigned int numOfVertices;
      unsigned int numOfIndices;

      GLuint renderingProgram;

public:
      Mesh(int id, const char *t);
      Mesh(int id, const char *t, GLuint rp);
      virtual ~Mesh();

      virtual void SetupBuffers();
      virtual void UpdateMesh();
      virtual void RenderMesh();
      void DestroyMesh();

      void Translate();
      void Rotate();
      void Scale();
};

#endif
