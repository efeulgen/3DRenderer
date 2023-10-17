
#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#include <iostream>
#include <glm/glm.hpp>

namespace DebugUtils
{
      void PrintMat4(glm::mat4 matrix)
      {
            std::cout << matrix[0][0] << " - ";
            std::cout << matrix[0][1] << " - ";
            std::cout << matrix[0][2] << " - ";
            std::cout << matrix[0][3] << std::endl;

            std::cout << matrix[1][0] << " - ";
            std::cout << matrix[1][1] << " - ";
            std::cout << matrix[1][2] << " - ";
            std::cout << matrix[1][3] << std::endl;

            std::cout << matrix[2][0] << " - ";
            std::cout << matrix[2][1] << " - ";
            std::cout << matrix[2][2] << " - ";
            std::cout << matrix[2][3] << std::endl;

            std::cout << matrix[3][0] << " - ";
            std::cout << matrix[3][1] << " - ";
            std::cout << matrix[3][2] << " - ";
            std::cout << matrix[3][3] << std::endl;
      }
}

#endif
