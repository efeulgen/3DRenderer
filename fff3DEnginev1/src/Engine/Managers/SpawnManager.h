
#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include <iostream>
#include "../Logger/Logger.h"

enum PrimitiveType
{
      CUBE,
      SPHERE,
      CONE,
      CYLINDER
};

class SpawnManager
{
public:
      SpawnManager();
      ~SpawnManager();

      void SpawnPrimitive(PrimitiveType primType);
};

#endif
