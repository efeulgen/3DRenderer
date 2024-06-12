
#include "InputManager.h"

InputManager::InputManager()
{
      Logger::Log("InputManager Constuctor");
}

InputManager::~InputManager()
{
      Logger::Log("InputManager Destructor");
}

void InputManager::ProcessInput(GLFWwindow *window)
{
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
            glfwSetWindowShouldClose(window, true);
      }
}

void InputManager::Destroy()
{
      delete this;
}
