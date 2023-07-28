
#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Shaders/Shader.h"
#include "Shaders/SurfaceShader.h"
#include "Shaders/StandardShader.h"
#include "Shaders/DirectionalShadowMapShader.h"
#include "Camera.h"
#include "Lights/Light.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Managers/InputManager.h"
#include "Managers/ImportManager.h"
#include "ShadowMaps/ShadowMap.h"
#include "ShadowMaps/DirectionalShadowMap.h"

#include "Logger/Logger.h"

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
      std::vector<SurfaceShader *> surfaceShaders;
      std::vector<Camera *> cameras;
      std::vector<Light *> lights;
      std::vector<ShadowMap *> shadowMaps;
      Camera *activeCamera = nullptr;
      DirectionalShadowMapShader *directionalShadowShdr = nullptr;
      DirectionalLight *mainDirectionalLight = nullptr;

      int pointLightCount;
      int spotLightCount;

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
      void RenderDirectionalShadowPass(DirectionalLight *dirLight);
      void RenderOmnidirectionalShadowPass();
      void RenderMainPass();
      void Render();
      void Destroy();

      void CreateNewPointLight(glm::vec3 pos = glm::vec3(5.0, 0.0, 0.0), glm::vec3 col = glm::vec3(1.0, 1.0, 1.0), float i = 1.0f);
      void CreateNewSpotLight(glm::vec3 pos = glm::vec3(5.0, 0.0, 0.0), glm::vec3 col = glm::vec3(1.0, 1.0, 1.0), float i = 1.0f, glm::vec3 dir = glm::vec3(0.0, -1.0, 0.0), float edge = 25.0f);
};

#endif
