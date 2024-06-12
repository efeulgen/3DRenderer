
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include "../Logger/Logger.h"

class InputManager
{
private:
public:
      InputManager();
      ~InputManager();

      void ProcessInput(GLFWwindow *window);
      void Destroy();
};

#endif
