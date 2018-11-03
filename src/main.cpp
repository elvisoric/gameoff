#include <glad/glad.h>

#include <core/loader.h>
#include <core/renderer.h>
#include <impl/basic_shader.h>
#include <window.h>
#include <helper.hpp>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

int main() {
  auto window = jam::createWindow(1024.0f, 768.0f);

  jam::shader::BasicShader shader;
  jam::Renderer renderer;
  jam::Loader loader;

  std::vector<float> vertices = {// positions
                                 1.0f,  1.0f,  0.0f, 1.0f,  -1.0f, 0.0f,
                                 -1.0f, -1.0f, 0.0f, -1.0f, 1.0f,  0.0f};
  std::vector<unsigned int> indices = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };
  std::vector<float> dummy;
  auto model = loader.loadVAO(vertices, dummy, dummy, indices);

  glm::mat4 trans{1.0f};
  trans = glm::translate(
      trans, glm::vec3{window.width() / 2, window.height() / 2, 0.0f});
  trans = glm::scale(trans, glm::vec3{50.0f});
  glm::mat4 projection =
      glm::ortho(0.0f, window.width(), window.height(), 0.0f, -1.0f, 1.0f);

  while (!window.shouldClose()) {
    renderer.newFrame();

    shader.start();

    shader.loadModel(trans);
    shader.loadProjection(projection);

    renderer.render(model);
    shader.stop();

    window.pollEvents();
    window.swapBuffers();
    jam::mojave_fix(window);
  }
  return 0;
}
