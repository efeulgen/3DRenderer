
#ifndef IMPORTMANAGER_H
#define IMPORTMANAGER_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Mesh.h"
#include "../Shaders/SurfaceShader.h"

#include "../Logger/Logger.h"

class ImportManager
{
public:
      static Mesh *Import(const char *path, const char *texPath, std::vector<Mesh *> &meshList, SurfaceShader *shader, glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0), float angle = 0.0f, glm::vec3 axis = glm::vec3(0.0, 1.0, 0.0), glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0));
};

#endif
