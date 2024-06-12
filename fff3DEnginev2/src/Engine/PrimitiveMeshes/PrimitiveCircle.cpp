
#include "PrimitiveCircle.h"

PrimitiveCircle::PrimitiveCircle(int id, const char *t) : Mesh(id, t)
{
      Logger::Log("PrimitiveCircle Constructor");
}

PrimitiveCircle::~PrimitiveCircle()
{
      Logger::Log("PrimitiveCircle Destructor");
}
