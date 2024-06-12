
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../Scene.h"
#include "../Logger/Logger.h"

class SceneManager
{
private:
      int sceneCount = 0;
      int currentSceneIndex = -1;
      Scene **scenes;

public:
      SceneManager();
      ~SceneManager();

      void AddScene();
      void LoadScene(int index);
      void ClearScenes();
      void Destroy();

      // getters & setters
      Scene *GetCurrentScene() const { return scenes[currentSceneIndex]; }
};

#endif
