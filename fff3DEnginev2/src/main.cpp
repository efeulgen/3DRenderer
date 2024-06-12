
#include <iostream>
#include "Engine/Engine.h"

#define windowWidth 1280
#define windowHeight 720

int main()
{
      if (!glfwInit())
      {
            Logger::Err("Error initializing GLFW");
            exit(EXIT_FAILURE);
      }
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      GLFWwindow *mainWindow = glfwCreateWindow(windowWidth, windowHeight, "FFF-3D Renderer v.02", NULL, NULL);
      glfwMakeContextCurrent(mainWindow);
      if (!mainWindow)
      {
            Logger::Err("Window creation fails.");
            glfwTerminate();
            exit(EXIT_FAILURE);
      }

      Engine fffEngine(windowWidth, windowHeight, mainWindow);

      if (glewInit() != GLEW_OK)
      {
            Logger::Err("Error initializing GLEW");
            glfwDestroyWindow(mainWindow);
            glfwTerminate();
            exit(EXIT_FAILURE);
      }

      glfwSwapInterval(1);

      fffEngine.Init();
      while (!glfwWindowShouldClose(mainWindow))
      {
            fffEngine.Display();

            glfwSwapBuffers(mainWindow);
            glfwPollEvents();
      }

      fffEngine.Destroy();
      glfwDestroyWindow(mainWindow);
      glfwTerminate();
      exit(EXIT_SUCCESS);
}
