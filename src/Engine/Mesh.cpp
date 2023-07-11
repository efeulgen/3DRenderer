
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
      if (shader)
      {
            delete shader;
      }
}

void Mesh::SetBuffers()
{
      unsigned int cubeIndices[] = {
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

      GLfloat cubeVertices[] = {
          -0.5, 0.5, -0.5,
          0.5, 0.5, -0.5,
          -0.5, 0.5, 0.5,
          0.5, 0.5, 0.5,
          -0.5, -0.5, -0.5,
          0.5, -0.5, -0.5,
          -0.5, -0.5, 0.5,
          0.5, -0.5, 0.5,
          -0.5, 0.5, 0.5,
          0.5, 0.5, 0.5,
          -0.5, -0.5, 0.5,
          0.5, -0.5, 0.5,
          -0.5, 0.5, -0.5,
          0.5, 0.5, -0.5,
          -0.5, -0.5, -0.5,
          0.5, -0.5, -0.5,
          -0.5, 0.5, 0.5,
          -0.5, 0.5, -0.5,
          -0.5, -0.5, 0.5,
          -0.5, -0.5, -0.5,
          0.5, 0.5, 0.5,
          0.5, 0.5, -0.5,
          0.5, -0.5, 0.5,
          0.5, -0.5, -0.5};

      glGenVertexArrays(numVAOs, vao);
      glBindVertexArray(vao[0]);

      glGenBuffers(numEBOs, ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

      glGenBuffers(numVBOs, vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::SetShader()
{
      shader = new Shader();
      shader->CreateRenderingProgram();
      uniformModelMatLocation = glGetUniformLocation(shader->GetRenderingProgram(), "model_mat");
      uniformProjectionMatLocation = glGetUniformLocation(shader->GetRenderingProgram(), "projection_mat");
      if (uniformModelMatLocation == -1 || uniformProjectionMatLocation == -1)
      {
            std::cout << "Uniforms not located." << std::endl;
      }
}

void Mesh::UpdateMesh()
{
}

void Mesh::RenderMesh(glm::mat4 projMat)
{
      glUseProgram(shader->GetRenderingProgram());

      glm::mat4 modelMat(1.0f);
      modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -5.0f));

      glUniformMatrix4fv(uniformModelMatLocation, 1, GL_FALSE, glm::value_ptr(modelMat));
      glUniformMatrix4fv(uniformProjectionMatLocation, 1, GL_FALSE, glm::value_ptr(projMat));

      glBindVertexArray(vao[0]);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
      glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);
}

void Mesh::DestroyMesh()
{
      delete this;
}
