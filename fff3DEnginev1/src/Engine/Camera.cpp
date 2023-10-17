
#include "Camera.h"

Camera::Camera(int frameBufferWidth, int frameBufferHeight)
{
      Logger::Log("Camera Constructor");

      projectionMat = glm::perspective(45.0f, (GLfloat)frameBufferWidth / (GLfloat)frameBufferHeight, 0.01f, 1000.0f);
}

Camera::~Camera()
{
      Logger::Log("Camera Destructor");
}

void Camera::ProcessCameraInput(GLFWwindow *window)
{
      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      {
            transform.position += frontVector * moveSpeed;
      }
      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      {
            transform.position -= frontVector * moveSpeed;
      }
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      {
            transform.position += rightVector * moveSpeed;
      }
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      {
            transform.position -= rightVector * moveSpeed;
      }
      if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
      {
            transform.position += upVector * moveSpeed;
      }
      if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
      {
            transform.position -= upVector * moveSpeed;
      }
}

void Camera::UpdateCamera(GLfloat *cursorChange)
{
      // viewMat = glm::mat4(1.0f);
      // viewMat = glm::translate(viewMat, transform.position);
      cursorChange[0] *= turnSpeed;
      cursorChange[1] *= turnSpeed;

      yaw += cursorChange[0];
      pitch += cursorChange[1];

      if (pitch > 89.0f)
      {
            pitch = 89.0f;
      }
      if (pitch < -89.0f)
      {
            pitch = -89.0f;
      }

      frontVector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
      frontVector.y = sin(glm::radians(pitch));
      frontVector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
      frontVector = glm::normalize(frontVector);
      rightVector = glm::normalize(glm::cross(frontVector, glm::vec3(0.0f, 1.0f, 0.0f)));
      upVector = glm::normalize(glm::cross(rightVector, frontVector));

      viewMat = glm::lookAt(transform.position, transform.position + frontVector, upVector);
}
