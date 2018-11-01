#ifndef JAM_WINDOW_H
#define JAM_WINDOW_H

#include <GLFW/glfw3.h>

namespace jam {

class Window {
 public:
  Window(GLFWwindow* window, float width, float height);
  virtual ~Window();

  inline void pollEvents() const { glfwPollEvents(); }
  inline void swapBuffers() const { glfwSwapBuffers(window_); }
  inline bool shouldClose() const { return glfwWindowShouldClose(window_); }
  inline GLFWwindow* window() { return window_; }
  inline float width() const { return width_; }
  inline float height() const { return height_; }

 private:
  GLFWwindow* window_;
  float width_;
  float height_;
};

Window createWindow(float width, float height);

}  // namespace jam

#endif  // JAM_WINDOW_H