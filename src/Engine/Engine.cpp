
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
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

      // create window
      window = glfwCreateWindow(1280, 720, "FFF-3D Renderer v.01", NULL, NULL);
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

      // set framebuffer
      glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
      glViewport(0, 0, frameBufferWidth, frameBufferHeight);
      glEnable(GL_DEPTH_TEST);
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
      // cameras
      cameras.push_back(new Camera(frameBufferWidth, frameBufferHeight));
      activeCamera = cameras[0];

      // meshes
      meshes.push_back(new Mesh(glm::vec3(0.0f, 0.0f, -5.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
      for (auto mesh : meshes)
      {
            mesh->SetBuffers();
            mesh->SetShader();
      }

      // lights
      lights.push_back(new Light());
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
      activeCamera->UpdateCamera();
}

void Engine::Render()
{
      glClearColor(0.1f, 0.1f, 0.11f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // render objects
      for (auto mesh : meshes)
      {
            mesh->RenderMesh(activeCamera, lights);
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
