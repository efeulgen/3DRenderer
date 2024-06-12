
#include "PrimitiveTorus.h"

PrimitiveTorus::PrimitiveTorus(int id, const char *t) : Mesh(id, t)
{
      Logger::Log("PrimitiveTorus Constructor");
}

PrimitiveTorus::~PrimitiveTorus()
{
      Logger::Log("PrimitiveTorus Destructor");
}
