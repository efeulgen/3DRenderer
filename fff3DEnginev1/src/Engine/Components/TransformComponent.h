
#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct Rotation
{
      float angle{0.0f};
      glm::vec3 axis{glm::vec3(0.0f, 1.0f, 0.0f)};
};

struct Transform
{
      glm::vec3 position{glm::vec3{0.0f, 0.0f, 0.0f}};
      Rotation rotation;
      glm::vec3 scale{glm::vec3{1.0f, 1.0f, 1.0f}};
};

#endif
