
#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Mesh.h"

class Engine
{
private:
      GLFWwindow *window;
      int windowWidth;
      int windowHeight;

      // scene objects
      std::vector<Mesh *> meshes;

public:
      Engine();
      Engine(int w, int h);
      ~Engine();

      void Init();
      void Display();
      void ProcessInput();
      void Update();
      void Render();
      void Destroy();
};

#endif
