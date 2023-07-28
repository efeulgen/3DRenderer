
#include "Mesh.h"

Mesh::Mesh()
{
      std::cout << "Default Mesh Constructor" << std::endl;
}

Mesh::Mesh(GLfloat *v, unsigned int *i, int v_size, int i_size)
{
      std::cout << "Mesh Constructor" << std::endl;

      vertices = v;
      indices = i;
      numOfVertices = v_size;
      numOfIndices = i_size;

      transform.position = glm::vec3(0.0, 0.0, 0.0);
      transform.rotation.angle = 0.0f;
      transform.rotation.axis = glm::vec3(0.0, 1.0, 0.0);
      transform.scale = glm::vec3(1.0, 1.0, 1.0);
}

Mesh::Mesh(GLfloat *v, unsigned int *i, int v_size, int i_size, glm::vec3 pos, float angle, glm::vec3 axis, glm::vec3 scale)
{
      std::cout << "Mesh Constructor" << std::endl;

      vertices = v;
      indices = i;
      numOfVertices = v_size;
      numOfIndices = i_size;

      transform.position = pos;
      transform.rotation.angle = angle;
      transform.rotation.axis = axis;
      transform.scale = scale;
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
      glBindVertexArray(0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::AssignShader(SurfaceShader *shdr, const char *texPath)
{
      texFilePath = texPath;
      texID = texFilePath ? Texture::CreateTexture(texFilePath) : 0;
      shader = shdr;
}

void Mesh::UpdateMesh()
{
}

void Mesh::RenderMesh(Camera *activeCam, DirectionalShadowMapShader *dirShadowShdr, DirectionalLight *dirLight, bool isRenderingShadowPass)
{
      if (!isRenderingShadowPass)
      {
            if (texFilePath) // implement in Material
            {
                  glActiveTexture(GL_TEXTURE0);
                  glBindTexture(GL_TEXTURE_2D, texID);
            }
            glUseProgram(shader->GetRenderingProgram());
      }

      // transform.rotation.angle += 1.f; // for debugging; delete later

      glm::mat4 modelMat(1.0f);
      modelMat = glm::translate(modelMat, transform.position);
      modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.angle), transform.rotation.axis);
      modelMat = glm::scale(modelMat, transform.scale);

      if (isRenderingShadowPass)
      {
            glUniformMatrix4fv(dirShadowShdr->GetUniformModelMatLocation(), 1, GL_FALSE, glm::value_ptr(modelMat));
      }
      else
      {
            glUniformMatrix4fv(shader->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMat));
      }
      glUniformMatrix4fv(dirShadowShdr->GetUniformDirectionalLightTransformLocation(), 1, GL_FALSE, glm::value_ptr(dirLight->GetLightTransform()));
      glUniformMatrix4fv(shader->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(activeCam->GetViewMatrix()));       // should be handled in camera
      glUniformMatrix4fv(shader->GetUniformLocation("proj"), 1, GL_FALSE, glm::value_ptr(activeCam->GetProjectionMatrix())); // should be handled in camera

      glBindVertexArray(vao[0]);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
      glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);
}

void Mesh::DestroyMesh()
{
      delete this;
}
