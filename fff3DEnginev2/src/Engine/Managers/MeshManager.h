
#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include "../Mesh.h"
#include "../PrimitiveMeshes/PrimitiveCube.h"
#include "../PrimitiveMeshes/PrimitiveTriangle.h"
#include "../Logger/Logger.h"

struct MeshManagerNode
{
      Mesh *mesh = nullptr;
      MeshManagerNode *next = nullptr;
};

class MeshManager
{
private:
      MeshManagerNode *head;
      MeshManagerNode *last;

public:
      MeshManager();
      ~MeshManager();

      void SetupMeshes();
      void UpdateMeshes();
      void RenderMeshes();

      void AddMesh(Mesh *mesh);
      void DestroyMesh();
      void FindMesh();
      void FindMeshWithTag();
      void ClearMeshes();

      void Destroy();
};

#endif
