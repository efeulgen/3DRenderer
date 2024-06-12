
#include "Engine.h"

Engine::Engine() : windowWidth{1280}, windowHeight{720}
{
      Logger::Log("Default Engine Constructor");
}

Engine::Engine(int w, int h, GLFWwindow *window) : windowWidth{w}, windowHeight{h}, mainWindow{window}
{
      Logger::Log("Overloaded Engine Constructor");
}

Engine::~Engine()
{
      Logger::Log("Engine Destructor");
}

void Engine::Init()
{
      inputManager = new InputManager();
      sceneManager = new SceneManager();
      sceneManager->AddScene();
}

void Engine::Display()
{
      inputManager->ProcessInput(mainWindow);
      sceneManager->GetCurrentScene()->UpdateScene();
      sceneManager->GetCurrentScene()->RenderScene();
}

void Engine::Destroy()
{
      inputManager->Destroy();
      sceneManager->Destroy();
      inputManager = nullptr;
      sceneManager = nullptr;
}
