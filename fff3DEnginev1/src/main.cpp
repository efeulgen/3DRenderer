
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "Engine/Engine.h"

int main()
{
      Engine engine;
      engine.Init();
      engine.Display();
      engine.Destroy();

      return 0;
}
