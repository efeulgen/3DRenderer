
#include "SceneManager.h"

SceneManager::SceneManager()
{
      Logger::Log("Scene Manager Constructor");
}

SceneManager::~SceneManager()
{
      Logger::Log("Scene Manager Destructor");
}

void SceneManager::AddScene()
{
      Scene *newScene = new Scene();
      newScene->InitScene();

      Scene **temp = new Scene *[sceneCount + 1];
      int i;
      for (i = 0; i < sceneCount; i++)
      {
            temp[i] = scenes[i];
      }
      temp[sceneCount] = newScene;

      if (sceneCount != 0)
      {
            delete[] scenes;
      }

      scenes = temp;
      temp = nullptr;

      sceneCount++;
      currentSceneIndex++;
}

void SceneManager::LoadScene(int index)
{
      currentSceneIndex = index;
}

void SceneManager::ClearScenes()
{
      for (int i = 0; i < sceneCount; i++)
      {
            scenes[i]->DestroyScene();
      }
}

void SceneManager::Destroy()
{
      ClearScenes();
      delete this;
}
