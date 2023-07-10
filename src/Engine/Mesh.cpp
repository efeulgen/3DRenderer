
#include "Mesh.h"

Mesh::Mesh()
{
      std::cout << "Mesh Constructor" << std::endl;
      unsigned int indexArray[] = {
          0, 1, 2,
          2, 3, 1,
          4, 5, 6,
          6, 7, 5,
          8, 9, 10,
          10, 11, 9,
          12, 13, 14,
          14, 15, 13,
          16, 17, 18,
          18, 19, 17,
          20, 21, 22,
          22, 23, 21};

      GLfloat vertexArray[] = {
          -1, 1, -1,
          1, 1, -1,
          -1, 1, 1,
          1, 1, 1,
          -1, -1, -1,
          1, -1, -1,
          -1, -1, 1,
          1, -1, 1,
          -1, 1, 1,
          1, 1, 1,
          -1, -1, 1,
          1, -1, 1,
          -1, 1, -1,
          1, 1, -1,
          -1, -1, -1,
          1, -1, -1,
          -1, 1, 1,
          -1, 1, -1,
          -1, -1, 1,
          -1, -1, -1,
          1, 1, 1,
          1, 1, -1,
          1, -1, 1,
          1, -1, -1};

      indices = indexArray;
      vertices = vertexArray;
}

Mesh::Mesh(GLfloat *v, unsigned int *i) : vertices{v}, indices{i}
{
}

Mesh::~Mesh()
{
      std::cout << "Mesh Destructor" << std::endl;
}

void Mesh::SetBuffers()
{
      glGenVertexArrays(numVAOs, vao);
      glBindVertexArray(vao[0]);

      glGenBuffers(numEBOs, ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      glGenBuffers(numVBOs, vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::UpdateMesh()
{
}

void Mesh::RenderMesh()
{
      glUseProgram(renderingProgram);
      glBindVertexArray(vao[0]);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
      glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);
}