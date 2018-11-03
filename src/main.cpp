#include <glad/glad.h>

#include <impl/basic_shader.h>
#include <window.h>
#include <helper.hpp>

int main() {
  auto window = jam::createWindow(1024.0f, 768.0f);

  jam::shader::BasicShader shader;

  while (!window.shouldClose()) {
    // TODO: resolve clearing screen in different way
    glClear(GL_COLOR_BUFFER_BIT);
    shader.start();
    shader.stop();

    window.pollEvents();
    window.swapBuffers();
    jam::mojave_fix(window);
  }
  return 0;
}
