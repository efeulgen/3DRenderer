
#include "SpawnManager.h"

SpawnManager::SpawnManager()
{
      std::cout << "SpawnManager Constructor" << std::endl;
}

SpawnManager::~SpawnManager()
{
      std::cout << "SpawnManager Destructor" << std::endl;
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
