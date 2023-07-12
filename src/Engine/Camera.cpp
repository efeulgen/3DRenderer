
#include "Camera.h"

Camera::Camera(int frameBufferWidth, int frameBufferHeight)
{
      std::cout << "Camera Constructor" << std::endl;

      projectionMat = glm::perspective(45.0f, (GLfloat)frameBufferWidth / (GLfloat)frameBufferHeight, 0.01f, 1000.0f);
}

Camera::~Camera()
{
      std::cout << "Camera Destructor" << std::endl;
}

void Camera::ProcessCameraInput(GLFWwindow *window)
{
      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      {
            transform.position -= glm::vec3(0.0f, 0.0f, 0.2f);
      }
      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      {
            transform.position += glm::vec3(0.0f, 0.0f, 0.2f);
      }
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      {
            transform.position += glm::vec3(0.2f, 0.0f, 0.0f);
      }
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      {
            transform.position -= glm::vec3(0.2f, 0.0f, 0.0f);
      }
}

void Camera::UpdateCamera()
{
      viewMat = glm::mat4(1.0f);
      viewMat = glm::translate(viewMat, transform.position);
}
