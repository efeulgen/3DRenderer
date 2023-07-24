
#ifndef IMPORTMANAGER_H
#define IMPORTMANAGER_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Mesh.h"

#include "../Logger/Logger.h"

class ImportManager
{
public:
      static Mesh *Import(const char *path);
};

#endif
