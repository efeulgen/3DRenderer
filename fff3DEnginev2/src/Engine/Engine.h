
#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logger/Logger.h"
#include "Managers/InputManager.h"
#include "Managers/SceneManager.h"

class Engine
{
private:
      int windowWidth;
      int windowHeight;
      GLFWwindow *mainWindow = nullptr;

      InputManager *inputManager = nullptr;
      SceneManager *sceneManager = nullptr;

public:
      Engine();
      Engine(int w, int h, GLFWwindow *window);
      ~Engine();

      void Init();
      void Display();
      void Destroy();
};

#endif
