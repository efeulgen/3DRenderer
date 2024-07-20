
#include "MeshManager.h"

MeshManager::MeshManager()
{
      Logger::Log("MeshManager Constructor");

      head = nullptr;
      last = nullptr;
}

MeshManager::~MeshManager()
{
      Logger::Log("MeshManager Destructor");
}

// *******************************************************************************************************************************************************************************
// *******************************************************************************************************************************************************************************

void MeshManager::SetupMeshes()
{
      if (!head)
            return;
      MeshManagerNode *p = head;
      while (p)
      {
            p->mesh->SetupBuffers();
            p = p->next;
      }
      p = nullptr;
}

void MeshManager::UpdateMeshes()
{
      if (!head)
            return;
      MeshManagerNode *p = head;
      while (p)
      {
            p->mesh->UpdateMesh();
            p = p->next;
      }
      p = nullptr;
}

void MeshManager::RenderMeshes()
{
      if (!head)
            return;
      MeshManagerNode *p = head;
      while (p)
      {
            p->mesh->RenderMesh();
            p = p->next;
      }
      p = nullptr;
}

// *******************************************************************************************************************************************************************************
// *******************************************************************************************************************************************************************************

void MeshManager::AddMesh(Mesh *mesh)
{
      MeshManagerNode *newNode = new MeshManagerNode;
      newNode->mesh = mesh;
      newNode->next = nullptr;

      if (!head)
      {
            head = last = newNode;
      }
      else
      {
            last->next = newNode;
            last = newNode;
      }
}

void MeshManager::DestroyMesh()
{
}

void MeshManager::FindMesh()
{
}

void MeshManager::FindMeshWithTag()
{
}

void MeshManager::ClearMeshes()
{
      if (!head)
            return;

      MeshManagerNode *p = head;
      while (p)
      {
            p->mesh->DestroyMesh();
            p = p->next;
      }
      p = nullptr;

      if (head == last)
      {
            delete head;
      }
      else
      {
            delete head;
            delete last;
      }

      head = nullptr;
      last = nullptr;
}

void MeshManager::Destroy()
{
      ClearMeshes();
      delete this;
}
