#include <glad/glad.h>

#include <core/loader.h>
#include <core/renderer.h>
#include <impl/basic_shader.h>
#include <window.h>
#include <helper.hpp>
#include <iostream>

int main() {
  auto window = jam::createWindow(1024.0f, 768.0f);

  jam::shader::BasicShader shader;
  jam::Renderer renderer;
  jam::Loader loader;

  std::vector<float> vertices = {// positions
                                 0.5f,  0.5f,  0.0f, 0.5f,  -0.5f, 0.0f,
                                 -0.5f, -0.5f, 0.0f, -0.5f, 0.5f,  0.0f};
  std::vector<unsigned int> indices = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };
  std::vector<float> dummy;
  auto model = loader.loadVAO(vertices, dummy, dummy, indices);

  while (!window.shouldClose()) {
    renderer.newFrame();

    shader.start();
    renderer.render(model);
    shader.stop();

    window.pollEvents();
    window.swapBuffers();
    jam::mojave_fix(window);
  }
  return 0;
}
