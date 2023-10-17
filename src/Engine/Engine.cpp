
#include "Engine.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Engine::Engine()
{
      Logger::Log("Engine Constructor");

      windowWidth = 1280;
      windowHeight = 720;
}

Engine::Engine(int w, int h) : windowWidth{w}, windowHeight{h}
{
      Logger::Log("Engine Constructor");
}

Engine::~Engine()
{
      Logger::Log("Engine Destructor");
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
      surfaceShaders.push_back(new StandardShader(pointLightCount, spotLightCount));
      for (auto shader : surfaceShaders)
      {
            shader->CreateRenderingProgram();
      }
      directionalShadowShdr = new DirectionalShadowMapShader();
      directionalShadowShdr->CreateRenderingProgram();

      // meshes
      ImportManager::Import("src/Engine/PrimitiveMeshes/torus.obj", "assets/tex/brick.png", meshes, surfaceShaders[0]);                            // TODO : debug; can't load . jpg !!
      ImportManager::Import("src/Engine/PrimitiveMeshes/plane.obj", "assets/tex/brick.png", meshes, surfaceShaders[0], glm::vec3(0.0, -2.0, 0.0)); // TODO : debug; can't load . jpg !!
      // ImportManager::Import("assets/geo/x-wing.obj"); // TODO : scale

      // lights
      mainDirectionalLight = new DirectionalLight(surfaceShaders);
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

void Engine::RenderDirectionalShadowPass(DirectionalLight *dirLight)
{
      glUseProgram(directionalShadowShdr->GetRenderingProgram());
      glBindFramebuffer(GL_FRAMEBUFFER, shadowMaps[0]->GetShadowBuffer());

      glClear(GL_DEPTH_BUFFER_BIT);
      // glDrawBuffer(GL_NONE);
      glUniformMatrix4fv(directionalShadowShdr->GetUniformDirectionalLightTransformLocation(), 1, GL_FALSE, glm::value_ptr(dirLight->GetLightTransform())); // pointer to value_ptr?

      for (auto mesh : meshes) // render objects
      {
            mesh->RenderMesh(activeCamera, directionalShadowShdr, mainDirectionalLight, true);
      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Engine::RenderOmnidirectionalShadowPass()
{
      // ****************************************
      // ***** TODO : implement *****************
      // ****************************************
}

void Engine::RenderMainPass()
{
      for (auto mesh : meshes) // render objects
      {
            mesh->RenderMesh(activeCamera, directionalShadowShdr, mainDirectionalLight, false);
      }

      for (auto shader : surfaceShaders)
      {
            shader->UpdateLightCounts();
      }

      for (auto light : lights)
      {
            light->UseLight();
      }

      glActiveTexture(GL_TEXTURE1);
      // glBindTexture(GL_TEXTURE_2D, shadowMaps[0]->GetShadowMap());
      glUniform1i(surfaceShaders[0]->GetTexLocation(), 0); // texture
      // glUniform1i(surfaceShaders[0]->GetShadowMapLocation(), 1); // shadow map
}

void Engine::Render()
{
      glClearColor(0.1f, 0.1f, 0.11f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // RenderDirectionalShadowPass(mainDirectionalLight);
      RenderMainPass();
      CheckOpenGLError();

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
      for (auto shader : surfaceShaders)
      {
            shader->IncrementPointLightCount();
            shader->SetPointLightUniformLocations();
      }
      lights.push_back(new PointLight(surfaceShaders, pos, col, i, pointLightCount));
}

void Engine::CreateNewSpotLight(glm::vec3 pos, glm::vec3 col, float i, glm::vec3 dir, float edge)
{
      spotLightCount++;
      for (auto shader : surfaceShaders)
      {
            shader->IncrementSpotLightCount();
            shader->SetSpotLightUniformLocations();
      }
      lights.push_back(new SpotLight(surfaceShaders, pos, col, i, dir, edge, spotLightCount));
}

void Engine::CheckOpenGLError()
{
      GLenum error;
      while ((error = glGetError()) != GL_NO_ERROR)
      {
            switch (error)
            {
            case GL_INVALID_ENUM:
                  Logger::Err("Invalid Enumeration");
                  break;
            case GL_INVALID_VALUE:
                  Logger::Err("Invalid Value");
                  break;
            case GL_INVALID_OPERATION:
                  Logger::Err("Invalid Operation");
                  break;
            default:
                  Logger::Err("OpenGL Error : ", error);
                  break;
            }
      }
}
