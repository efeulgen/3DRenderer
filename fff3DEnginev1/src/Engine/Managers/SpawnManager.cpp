
#include "SpawnManager.h"

SpawnManager::SpawnManager()
{
      Logger::Log("SpawnManager Constructor");
}

SpawnManager::~SpawnManager()
{
      Logger::Log("SpawnManager Destructor");
}

void SpawnManager::SpawnPrimitive(PrimitiveType primType)
{
      switch (primType)
      {
      case PrimitiveType::CUBE:
            // spawn cube
            break;
      case PrimitiveType::CONE:
            // spawn cone
            break;
      case PrimitiveType::CYLINDER:
            // spawn cylinder
            break;
      case PrimitiveType::SPHERE:
            // spawn sphere
            break;
      default:
            break;
      }
}
