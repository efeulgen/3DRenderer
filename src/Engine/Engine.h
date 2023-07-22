
#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Shaders/Shader.h"
#include "Shaders/StandardShader.h"
#include "Camera.h"
#include "Lights/Light.h"
#include "Lights/DirectionalLight.h"
#include "Managers/InputManager.h"

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
      std::vector<StandardShader *> shaders; // for debugging : Shader*
      std::vector<Camera *> cameras;
      std::vector<DirectionalLight *> lights; // for debugging : Light*
      Camera *activeCamera = nullptr;

      // managers
      InputManager *inputManager;

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
