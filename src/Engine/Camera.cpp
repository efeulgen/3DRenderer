
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

void Camera::ProcessCameraInput()
{
}

void Camera::UpdateCamera()
{
}
