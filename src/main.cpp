#include <glad/glad.h>

#include <window.h>
#include <helper.hpp>

int main() {
  auto window = jam::createWindow(1024.0f, 768.0f);

  while (!window.shouldClose()) {
    // TODO: resolve clearing screen in different way
    glClear(GL_COLOR_BUFFER_BIT);

    window.pollEvents();
    window.swapBuffers();
    jam::mojave_fix(window);
  }
  return 0;
}
