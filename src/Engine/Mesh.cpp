
#include "Mesh.h"

Mesh::Mesh(glm::vec3 pos, float angle, glm::vec3 axis, glm::vec3 scale)
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

      transform.position = pos;
      transform.rotation.angle = angle;
      transform.rotation.axis = axis;
      transform.scale = scale;
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

      GLfloat normals[] = {
          -1.0f, 0.0f, 0.0f, // Left Side
          0.0f, 0.0f, -1.0f, // Back Side
          0.0f, -1.0f, 0.0f, // Bottom Side
          0.0f, 0.0f, -1.0f, // Back Side
          -1.0f, 0.0f, 0.0f, // Left Side
          0.0f, -1.0f, 0.0f, // Bottom Side
          0.0f, 0.0f, 1.0f,  // front Side
          1.0f, 0.0f, 0.0f,  // right Side
          1.0f, 0.0f, 0.0f,  // right Side
          0.0f, 1.0f, 0.0f,  // top Side
          0.0f, 1.0f, 0.0f,  // top Side
          0.0f, 0.0f, 1.0f,  // front Side

      };

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

      glGenBuffers(numNBOs, nbo);
      glBindBuffer(GL_ARRAY_BUFFER, nbo[0]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(1);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::SetShader()
{
      shader = new Shader();
      shader->CreateRenderingProgram();
      uniformModelMatLocation = glGetUniformLocation(shader->GetRenderingProgram(), "model_mat");
      uniformViewMatLocation = glGetUniformLocation(shader->GetRenderingProgram(), "view_mat");
      uniformProjectionMatLocation = glGetUniformLocation(shader->GetRenderingProgram(), "projection_mat");
      uniformLightPosLocation = glGetUniformLocation(shader->GetRenderingProgram(), "lightPos");
      uniformLightColorLocation = glGetUniformLocation(shader->GetRenderingProgram(), "lightColor");
      if (uniformModelMatLocation == -1 || uniformViewMatLocation == -1 || uniformProjectionMatLocation == -1 || uniformLightPosLocation == -1 || uniformLightColorLocation == -1)
      {
            std::cout << "Uniform(s) not located." << std::endl;
      }
}

void Mesh::UpdateMesh()
{
}

void Mesh::RenderMesh(Camera *activeCam, std::vector<Light *> lights)
{
      glUseProgram(shader->GetRenderingProgram());

      transform.rotation.angle += 1.f; // for debugging; delete later

      glm::mat4 modelMat(1.0f);
      modelMat = glm::translate(modelMat, transform.position);
      modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.angle), transform.rotation.axis);
      modelMat = glm::scale(modelMat, transform.scale);

      glUniformMatrix4fv(uniformModelMatLocation, 1, GL_FALSE, glm::value_ptr(modelMat));
      glUniformMatrix4fv(uniformViewMatLocation, 1, GL_FALSE, glm::value_ptr(activeCam->GetViewMatrix()));
      glUniformMatrix4fv(uniformProjectionMatLocation, 1, GL_FALSE, glm::value_ptr(activeCam->GetProjectionMatrix()));
      for (auto light : lights)
      {
            glUniform3f(uniformLightPosLocation, light->GetLightPos()[0], light->GetLightPos()[1], light->GetLightPos()[2]);
            glUniform3f(uniformLightColorLocation, light->GetLightColor()[0], light->GetLightColor()[1], light->GetLightColor()[2]);
      }

      glBindVertexArray(vao[0]);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
      glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);
}

void Mesh::DestroyMesh()
{
      delete this;
}
