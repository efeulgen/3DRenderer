
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <iostream>
#include <GLFW/glfw3.h>
#include "../Logger/Logger.h"

class InputManager
{
private:
      GLfloat cursorChange[2] = {0.0f, 0.0f};
      GLfloat cursorLastPos[2] = {0.0f, 0.0f};
      bool movesForTheFirstTime = true;

public:
      InputManager(GLFWwindow *window);
      ~InputManager();

      // getters & setters
      GLfloat *GetCursorChange() { return cursorChange; }

private:
      static void CursorCallback(GLFWwindow *window, double x, double y);
};

#endif
