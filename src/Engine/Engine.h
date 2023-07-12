
#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

class Engine
{
private:
      GLFWwindow *window;
      int windowWidth;
      int windowHeight;
      int frameBufferWidth;
      int frameBufferHeight;

      // scene objects
      std::vector<Mesh *> meshes;
      std::vector<Camera *> cameras;
      std::vector<Light *> lights;
      Camera *activeCamera = nullptr;

public:
      Engine();
      Engine(int w, int h);
      ~Engine();

      void Init();
      void Display();

      void SetupSceneObjects();
      void ProcessInput();
      void Update();
      void Render();
      void Destroy();
};

#endif
