
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders/Shader.h"
#include "Shaders/SurfaceShader.h"
#include "Shaders/DirectionalShadowMapShader.h"
#include "Lights/DirectionalLight.h"
#include "Camera.h"
#include "Texture.h"
#include "Components/TransformComponent.h"

#include "Logger/Logger.h"

#define numVAOs 1
#define numVBOs 1
#define numEBOs 1
#define numNBOs 1

class Mesh
{
private:
      SurfaceShader *shader = nullptr;
      GLuint vao[numVAOs];
      GLuint vbo[numVBOs];
      GLuint ebo[numEBOs];

      GLuint texID = -1;            // implement in Material
      const char *texFilePath = ""; // implement in Material

      GLfloat *vertices;
      unsigned int *indices;
      unsigned int numOfVertices;
      unsigned int numOfIndices;

      Transform transform;

public:
      Mesh();
      Mesh(GLfloat *v, unsigned int *i, int v_size, int i_size);
      Mesh(GLfloat *v, unsigned int *i, int v_size, int i_size, glm::vec3 pos, float angle, glm::vec3 axis, glm::vec3 scale);
      ~Mesh();

      void SetBuffers();
      void AssignShader(SurfaceShader *shdr, const char *texPath = "");
      void UpdateMesh();
      void RenderMesh(Camera *activeCam, DirectionalShadowMapShader *dirShadowShdr, DirectionalLight *dirLight, bool isRenderingShadowPass = false);
      void DestroyMesh();

      // getters & setters
      SurfaceShader *GetShader() { return shader; }
};

#endif
