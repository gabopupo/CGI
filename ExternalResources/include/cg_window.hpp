#ifndef __CG_WINDOW_HPP__
#define __CG_WINDOW_HPP__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtx/transform.hpp> // glm::translate, glm::rotate, glm::scale
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
  void run();

protected:
  void processInput(GLFWwindow *window);

  int _viewPortSize;
  GLFWwindow *_window;
  bool stopRotation;
  float rotationAngle;
  float rotationSpeed;
  const float SPEED_VAR = 0.00003f;
};
}

#endif