
#include "InputManager.h"

InputManager::InputManager(GLFWwindow *window)
{
      std::cout << "InputManager Constructor" << std::endl;

      glfwSetWindowUserPointer(window, this);
      glfwSetCursorPosCallback(window, CursorCallback);
}

InputManager::~InputManager()
{
      std::cout << "InputManager Destructor" << std::endl;
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
