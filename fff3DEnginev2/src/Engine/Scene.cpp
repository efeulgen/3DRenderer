
#include "Scene.h"

Scene::Scene()
{
      Logger::Log("Default Scene Constructor");

      meshManager = nullptr;
}

Scene::~Scene()
{
      Logger::Log("Scene Destructor");
}

void Scene::InitScene()
{
      // virtual function; implemented for testing

      meshManager = new MeshManager();
      meshManager->AddMesh(new PrimitiveTriangle(0, "triangle_01"));
      // meshManager->AddMesh(new PrimitiveTriangle(1, "triangle_02"));
      //  meshManager->AddMesh(new PrimitiveCube(0, "cube_01"));
      meshManager->SetupMeshes();
}

void Scene::UpdateScene()
{
      meshManager->UpdateMeshes();
}

void Scene::RenderScene()
{
      glClearColor(0.1, 0.1, 0.11, 1.0);
      glClear(GL_COLOR_BUFFER_BIT); //  | GL_DEPTH_BUFFER_BIT
      meshManager->RenderMeshes();
}

void Scene::DestroyScene()
{
      meshManager->Destroy();
      delete this;
}