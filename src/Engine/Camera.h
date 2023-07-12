
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Components/TransformComponent.h"

class Camera
{
private:
      glm::mat4 projectionMat;
      glm::mat4 viewMat;

      Transform transform;

public:
      Camera(int frameBufferWidth, int frameBufferHeight);
      ~Camera();

      void ProcessCameraInput(GLFWwindow *window);
      void UpdateCamera();

      // getters & setters
      glm::mat4 GetProjectionMatrix() const { return projectionMat; }
      glm::mat4 GetViewMatrix() const { return viewMat; }
};

#endif
