
#ifndef SCENE_H
#define SCENE_H

#include "Logger/Logger.h"
#include "Managers/MeshManager.h"

class Scene
{
private:
      MeshManager *meshManager;

public:
      Scene();
      virtual ~Scene();

      virtual void InitScene();
      void UpdateScene();
      void RenderScene();
      void DestroyScene();
};

#endif
