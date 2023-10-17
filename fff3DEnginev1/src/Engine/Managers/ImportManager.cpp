
#include "ImportManager.h"

std::vector<GLfloat> LoadVertices(aiNode *node, const aiScene *scene, std::vector<GLfloat> &vertices)
{
      for (int i = 0; i < node->mNumMeshes; i++)
      {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            for (int i = 0; i < mesh->mNumVertices; i++)
            {
                  vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
                  if (mesh->mTextureCoords[0])
                  {
                        vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
                  }
                  else
                  {
                        vertices.insert(vertices.end(), {0.0f, 0.0f});
                  }
                  vertices.insert(vertices.end(), {-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z});
            }
      }

      for (int i = 0; i < node->mNumChildren; i++)
      {
            LoadVertices(node->mChildren[i], scene, vertices);
      }

      return vertices;
}

std::vector<unsigned int> LoadIndices(aiNode *node, const aiScene *scene, std::vector<unsigned int> &indices)
{
      for (int i = 0; i < node->mNumMeshes; i++)
      {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            for (int i = 0; i < mesh->mNumFaces; i++)
            {
                  aiFace face = mesh->mFaces[i];
                  for (int j = 0; j < face.mNumIndices; j++)
                  {
                        indices.push_back(face.mIndices[j]);
                  }
            }
      }

      for (int i = 0; i < node->mNumChildren; i++)
      {
            LoadIndices(node->mChildren[i], scene, indices);
      }

      return indices;
}

Mesh *ImportManager::Import(const char *path, const char *texPath, std::vector<Mesh *> &meshList, SurfaceShader *shader, glm::vec3 pos, float angle, glm::vec3 axis, glm::vec3 scale)
{
      Assimp::Importer importer;
      const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
      if (!scene)
      {
            Logger::Err("Scene failed to load.");
      }

      std::vector<GLfloat> tempVertices;
      std::vector<unsigned int> tempIndices;

      LoadVertices(scene->mRootNode, scene, tempVertices);
      LoadIndices(scene->mRootNode, scene, tempIndices);

      GLfloat *vertices = new GLfloat[tempVertices.size()];
      unsigned int *indices = new unsigned int[tempIndices.size()];

      for (int i = 0; i < tempVertices.size(); i++)
      {
            vertices[i] = tempVertices[i];
      }

      for (int i = 0; i < tempIndices.size(); i++)
      {
            indices[i] = tempIndices[i];
      }

      Mesh *newMesh = new Mesh(vertices, indices, tempVertices.size(), tempIndices.size(), pos, angle, axis, scale);
      newMesh->AssignShader(shader, texPath);
      newMesh->SetBuffers();
      meshList.push_back(newMesh);
      return newMesh;
}
