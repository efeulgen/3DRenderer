
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

void Engine::SetupSceneObjects()
{
      //*pointLightCount = 0;
      //*spotLightCount = 0;
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
      meshes.push_back(new Mesh(glm::vec3(0.0f, 0.0f, -5.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), shaders[0], "assets/textures/brick.png"));
      for (auto mesh : meshes)
      {
            mesh->SetBuffers();
      }

      // lights
      lights.push_back(new DirectionalLight(shaders));
      CreateNewPointLight(glm::vec3(5.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), 1.0f);
      CreateNewPointLight(glm::vec3(-5.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), 1.0f);
}

void Engine::ProcessInput()
{
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
            glfwSetWindowShouldClose(window, GL_TRUE);
      }
      activeCamera->ProcessCameraInput(window);
}

void Engine::Update()
{
      // update objects
      for (auto mesh : meshes)
      {
            mesh->UpdateMesh();
      }
      activeCamera->UpdateCamera(inputManager->GetCursorChange());
}

void Engine::Render()
{
      glClearColor(0.1f, 0.1f, 0.11f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      for (auto shader : shaders)
      {
            shader->UpdateLightCounts();
      }

      for (auto light : lights)
      {
            light->UseLight();
      }

      // render objects
      for (auto mesh : meshes)
      {
            mesh->RenderMesh(activeCamera);
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
}

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

void Engine::CreateNewPointLight(glm::vec3 pos, glm::vec3 col, float i)
{
      //(*pointLightCount) += 1;
      pointLightCount++;
      for (auto shader : shaders)
      {
            shader->IncrementPointLightCount();
            shader->SetPointLightUniformLocations();
            // shader->UpdateLightCounts();
      }
      lights.push_back(new PointLight(shaders, pos, col, i, pointLightCount));
}
