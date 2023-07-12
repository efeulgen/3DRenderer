
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
      glm::mat4 projectionMat;

public:
      Camera(int frameBufferWidth, int frameBufferHeight);
      ~Camera();

      void ProcessCameraInput();
      void UpdateCamera();

      // getters & setters
      glm::mat4 GetProjectionMatrix() const { return projectionMat; }
};

#endif
