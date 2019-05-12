#ifndef __CG_WINDOW_HPP__
#define __CG_WINDOW_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <iostream>

namespace cgicmc {

class Window {
public:
  ///
  /// Instantiates glfw environment
  Window();

  ///
  /// Finalizes glfw environment
  ~Window();

  ///
  /// Create a single window with the specified size
  void createWindow(int, int);

  ///
  /// Run the application in a loop.
  void run(const char *);

protected:
  void processInput(GLFWwindow *window);

  // openGL variables
  GLFWwindow *_window;

  // translation variables
  float angleX, angleY, angleZ;
  const float ROT_VAR = 0.01f;

  // rotation variables
  float dimension;
  const float SCA_VAR = 0.001f;
};
}

#endif