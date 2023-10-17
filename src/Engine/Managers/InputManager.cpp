
#include "InputManager.h"

InputManager::InputManager(GLFWwindow *window)
{
      Logger::Log("InputManager Constructor");

      glfwSetWindowUserPointer(window, this);
      glfwSetCursorPosCallback(window, CursorCallback);
}

InputManager::~InputManager()
{
      Logger::Log("InputManager Destructor");
}

void InputManager::CursorCallback(GLFWwindow *window, double x, double y)
{
      InputManager *inpManager = static_cast<InputManager *>(glfwGetWindowUserPointer(window));
      if (inpManager->movesForTheFirstTime)
      {
            inpManager->cursorLastPos[0] = x;
            inpManager->cursorLastPos[1] = y;
            inpManager->movesForTheFirstTime = false;
      }
      inpManager->cursorChange[0] = x - inpManager->cursorLastPos[0];
      inpManager->cursorChange[1] = inpManager->cursorLastPos[1] - y;

      inpManager->cursorLastPos[0] = x;
      inpManager->cursorLastPos[1] = y;
}
