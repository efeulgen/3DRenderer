
#include "PrimitiveTriangle.h"

PrimitiveTriangle::PrimitiveTriangle(int id, const char *t) : Mesh(id, t)
{
      Logger::Log("PrimitiveTriangle Constructor");
}

PrimitiveTriangle::~PrimitiveTriangle()
{
      Logger::Log("PrimitiveTriangle Destructor");
}

void PrimitiveTriangle::SetupBuffers()
{
      GLfloat v[] = {
          -1.0, -1.0, 0.0,
          1.0, -1.0, 0.0,
          0.0, 1.0, 0.0};

      glGenVertexArrays(numVAOs, vao);
      glBindVertexArray(vao[0]);

      glGenBuffers(numVBOs, vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

      std::cout << "PrimitiveTriangle buffers set." << std::endl;
}

void PrimitiveTriangle::RenderMesh()
{
      glUseProgram(renderingProgram);
      glBindVertexArray(vao[0]);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // *************** for debug ****************************************************************************************************
      // glPointSize(30.0);
      // glDrawArrays(GL_POINTS, 0, 1);
}
