
#include "Mesh.h"

Mesh::Mesh(int id, const char *t) : meshID{id}, tag{t}
{
      Logger::Log("Mesh Constructor");

      MonochromeShader newMonochromeShader;
      newMonochromeShader.CreateRenderingProgram();
      renderingProgram = newMonochromeShader.GetRenderingProgram();
}

Mesh::Mesh(int id, const char *t, GLuint rp) : meshID{id}, tag{t}, renderingProgram{rp}
{
      Logger::Log("Overloaded Mesh Constructor");
}

Mesh::~Mesh()
{
      Logger::Log("Mesh Destructor");
}

void Mesh::SetupBuffers()
{
      glGenVertexArrays(numVAOs, vao);
      glBindVertexArray(vao[0]);

      glGenBuffers(numEBOs, ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

      glGenBuffers(numVBOs, vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);                                 // vertex pos
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void *)(sizeof(vertices[0]) * 5)); // normal
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void *)(sizeof(vertices[0]) * 3)); // uv
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
}

void Mesh::UpdateMesh()
{
}

void Mesh::RenderMesh()
{
      glUseProgram(renderingProgram);
      glBindVertexArray(vao[0]);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
      glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);
}

void Mesh::DestroyMesh()
{
      delete vertices;
      vertices = nullptr;
      delete indices;
      indices = nullptr;
      delete this;
}

void Mesh::Translate()
{
}

void Mesh::Rotate()
{
}

void Mesh::Scale()
{
}
