
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
#include "Logger/Logger.h"

class Camera
{
private:
      glm::mat4 projectionMat;
      glm::mat4 viewMat;

      Transform transform;

      glm::vec3 frontVector = glm::vec3(0.0f, 0.0f, -1.0f);
      glm::vec3 rightVector;
      glm::vec3 upVector;

      GLfloat yaw = -90.0f;
      GLfloat pitch = 0.0f;
      GLfloat turnSpeed = 0.1f;
      GLfloat moveSpeed = 0.5f;

public:
      Camera(int frameBufferWidth, int frameBufferHeight);
      ~Camera();

      void ProcessCameraInput(GLFWwindow *window);
      void UpdateCamera(GLfloat *cursorChange);

      // getters & setters
      glm::mat4 GetProjectionMatrix() const { return projectionMat; }
      glm::mat4 GetViewMatrix() const { return viewMat; }
};

#endif
