
#ifndef DIFFUSESHADER_H
#define DIFFUSESHADER_H

#include "Shader.h"

class DiffuseShader : public Shader
{
public:
      DiffuseShader();
      ~DiffuseShader();

      void CreateRenderingProgram() override;
};

#endif
