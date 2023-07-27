
#include "Engine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Engine::Engine()
{
      windowWidth = 1280;
      windowHeight = 720;
}

Engine::Engine(int w, int h) : windowWidth{w}, windowHeight{h}
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
      // init GLFW
      if (!glfwInit())
      {
            exit(EXIT_FAILURE);
      }
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      // create window
      GLFWmonitor *monitor = glfwGetPrimaryMonitor();
      const GLFWvidmode *mode = glfwGetVideoMode(monitor);
      window = glfwCreateWindow(mode->width, mode->height, "FFF-3D Renderer v.01", monitor, NULL);
      if (!window)
      {
            glfwTerminate();
            return;
      }
      glfwMakeContextCurrent(window);

      // init GLEW
      if (glewInit() != GLEW_OK)
      {
            exit(EXIT_FAILURE);
      }

      // set viewport
      glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
      glViewport(0, 0, frameBufferWidth, frameBufferHeight);

      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

      glEnable(GL_DEPTH_TEST); // | GL_ALPHA_TEST
}

void Engine::Display()
{
      SetupSceneObjects();
      while (!glfwWindowShouldClose(window))
      {
            ProcessInput();
            Update();
            Render();
      }
}

// ************************************************************************************************************************************************************************************
// *************** SETUP **************************************************************************************************************************************************************
// ************************************************************************************************************************************************************************************

void Engine::SetupSceneObjects()
{
      pointLightCount = 0;
      spotLightCount = 0;

      // managers
      inputManager = new InputManager(window);

      // cameras
      cameras.push_back(new Camera(frameBufferWidth, frameBufferHeight));
      activeCamera = cameras[0];

      // shaders
      shaders.push_back(new StandardShader(pointLightCount, spotLightCount));
      for (auto shader : shaders)
      {
            shader->CreateRenderingProgram();
      }

      // meshes
      ImportManager::Import("src/Engine/PrimitiveMeshes/torus.obj", "assets/tex/brick.png", meshes, shaders[0]); // TODO : debug; can't load . jpg !!
      // ImportManager::Import("assets/geo/x-wing.obj"); // TODO : scale

      // lights
      lights.push_back(new DirectionalLight(shaders));
      CreateNewPointLight(glm::vec3(5.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), 1.0f);
      CreateNewPointLight(glm::vec3(-5.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), 1.0f);
      CreateNewSpotLight(glm::vec3(0.0, 5.0, 0.0), glm::vec3(0.0, 0.0, 1.0), 1.0f, glm::vec3(0.0, -1.0, 0.0), 0.0f); // TODO Debug : edge doesn't work!!

      // shadow maps
      shadowMaps.push_back(new DirectionalShadowMap(1024, 1024));
      for (auto map : shadowMaps)
      {
            map->SetBuffers();
      }
}

// ************************************************************************************************************************************************************************************
// *************** INPUT **************************************************************************************************************************************************************
// ************************************************************************************************************************************************************************************

void Engine::ProcessInput()
{
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
            glfwSetWindowShouldClose(window, GL_TRUE);
      }
      activeCamera->ProcessCameraInput(window);
}

// ************************************************************************************************************************************************************************************
// *************** UPDATE *************************************************************************************************************************************************************
// ************************************************************************************************************************************************************************************

void Engine::Update()
{
      for (auto mesh : meshes) // update objects
      {
            mesh->UpdateMesh();
      }
      activeCamera->UpdateCamera(inputManager->GetCursorChange());
}

// ************************************************************************************************************************************************************************************
// *************** RENDER *************************************************************************************************************************************************************
// ************************************************************************************************************************************************************************************

void Engine::RenderDirectionalShadowPass()
{
      // use shader
      glBindFramebuffer(GL_FRAMEBUFFER, shadowMaps[0]->GetShadowBuffer());

      glDrawBuffer(GL_NONE);

      for (auto mesh : meshes) // render objects
      {
            mesh->RenderMesh(activeCamera);
      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Engine::RenderOmnidirectionalShadowPass()
{
      // TODO : implement
}

void Engine::RenderMainPass()
{
      for (auto shader : shaders)
      {
            shader->UpdateLightCounts();
      }

      for (auto light : lights)
      {
            light->UseLight();
      }

      for (auto mesh : meshes) // render objects
      {
            mesh->RenderMesh(activeCamera);
      }
}

void Engine::Render()
{
      glClearColor(0.1f, 0.1f, 0.11f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      RenderDirectionalShadowPass();
      RenderMainPass();

      glfwSwapBuffers(window);
      glfwPollEvents();
}

// ************************************************************************************************************************************************************************************
// *************** DESTROY ************************************************************************************************************************************************************
// ************************************************************************************************************************************************************************************

void Engine::Destroy()
{
      for (auto mesh : meshes)
      {
            mesh->DestroyMesh();
            mesh = nullptr;
      }
      glfwDestroyWindow(window);
      glfwTerminate();
}

// ************************************************************************************************************************************************************************************
// *************** UTILS **************************************************************************************************************************************************************
// ************************************************************************************************************************************************************************************

void Engine::CreateNewPointLight(glm::vec3 pos, glm::vec3 col, float i)
{
      pointLightCount++;
      for (auto shader : shaders)
      {
            shader->IncrementPointLightCount();
            shader->SetPointLightUniformLocations();
      }
      lights.push_back(new PointLight(shaders, pos, col, i, pointLightCount));
}

void Engine::CreateNewSpotLight(glm::vec3 pos, glm::vec3 col, float i, glm::vec3 dir, float edge)
{
      spotLightCount++;
      for (auto shader : shaders)
      {
            shader->IncrementSpotLightCount();
            shader->SetSpotLightUniformLocations();
      }
      lights.push_back(new SpotLight(shaders, pos, col, i, dir, edge, spotLightCount));
}
