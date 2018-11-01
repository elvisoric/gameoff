#ifndef JAM_HELPER_HPP
#define JAM_HELPER_HPP

#include <window.h>

namespace jam {
inline void mojave_fix(jam::Window& window) {
#ifdef __APPLE__
  static bool macMoved = false;

  if (!macMoved) {
    int x, y;
    glfwGetWindowPos(window.window(), &x, &y);
    glfwSetWindowPos(window.window(), ++x, y);
    macMoved = true;
  }
#endif
}

}  // namespace jam
#endif  // JAM_HELPER_HPP