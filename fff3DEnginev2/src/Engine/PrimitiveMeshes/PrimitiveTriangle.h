
#ifndef PRIMITIVETRIANGLE_H
#define PRIMITIVETRIANGLE_H

#include "../Mesh.h"

class PrimitiveTriangle : public Mesh
{
private:
public:
      PrimitiveTriangle(int id, const char *t);
      ~PrimitiveTriangle();

      void SetupBuffers() override;
      void RenderMesh() override;
      void DestroyMesh() override;
};

#endif
