
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Light.h"
#include "Camera.h"
#include "Texture.h"
#include "Components/TransformComponent.h"

#define numVAOs 1
#define numVBOs 1
#define numEBOs 1
#define numNBOs 1

class Mesh
{
private:
      Shader *shader = nullptr;
      GLuint vao[numVAOs];
      GLuint vbo[numVBOs];
      GLuint ebo[numEBOs];
      GLuint nbo[numNBOs];

      GLuint uniformModelMatLocation;
      GLuint uniformViewMatLocation;
      GLuint uniformProjectionMatLocation;
      GLuint uniformLightPosLocation;
      GLuint uniformLightColorLocation;

      GLuint texID;
      const char *texFilePath;

      GLfloat *vertices = nullptr;
      unsigned int *indices = nullptr;

      Transform transform;

public:
      Mesh(glm::vec3 pos, float angle, glm::vec3 axis, glm::vec3 scale, const char *path = "");
      Mesh(GLfloat *v, unsigned int *i);
      ~Mesh();

      void SetBuffers();
      void SetShader();
      void UpdateMesh();
      void RenderMesh(Camera *activeCam, std::vector<Light *> lights);
      void DestroyMesh();

      // getters & setters
      Shader *GetShader() { return shader; }
};

#endif
