#ifndef JAM_WINDOW_H
#define JAM_WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

namespace jam {

class Window {
 public:
  Window(GLFWwindow* window, float width, float height)
      : window_{window}, width_{width}, height_{height} {}
  virtual ~Window() { glfwDestroyWindow(window_); }

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

inline GLFWwindow* createWindow(float width, float height,
                                const std::string& title) {
  if (!glfwInit()) {
    throw "Failed to initialize glfw";
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow* window =
      glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    throw "Failed to create glfw window ";
  }
  glfwMakeContextCurrent(window);

  // initialize glad before any opengl call
  //   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
  //     throw "Failed to initialize GLAD";
  //   }
  return window;
}

inline Window createWindow(float width, float height) {
  auto windowPtr = createWindow(width, height, "GameOff");
  return Window{windowPtr, width, height};
}

}  // namespace jam

#endif  // JAM_WINDOW_H