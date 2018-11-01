#include <glad/glad.h>

#include <window.h>
#include <string>

namespace {

GLFWwindow* createWindow(float width, float height, const std::string& title) {
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
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw "Failed to initialize GLAD";
  }

  return window;
}

}  // anonymous namespace

namespace jam {

Window::Window(GLFWwindow* window, float width, float height)
    : window_{window}, width_{width}, height_{height} {}

Window::~Window() { glfwDestroyWindow(window_); }

Window createWindow(float width, float height) {
  auto windowPtr = ::createWindow(width, height, "GameOff");
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  return Window{windowPtr, width, height};
}

}  // namespace jam