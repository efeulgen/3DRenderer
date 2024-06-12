
#ifndef MONOCHROMESHADER_H
#define MONOCHROMESHADER_H

#include "Shader.h"

class MonochromeShader : public Shader
{
private:
public:
      MonochromeShader();
      ~MonochromeShader();

      void CreateRenderingProgram() override;
};

#endif
