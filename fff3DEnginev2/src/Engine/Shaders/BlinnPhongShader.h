
#ifndef BLINNPHONGSHADER_H
#define BLINNPHONGSHADER_H

#include "Shader.h"

class BlinnPhongShader : public Shader
{
public:
      BlinnPhongShader();
      ~BlinnPhongShader();

      void CreateRenderingProgram() override;
};

#endif
