#include <glad/glad.h>

#include <core/loader.h>
#include <core/renderer.h>
#include <impl/basic_shader.h>
#include <window.h>
#include <entt.hpp>
#include <factory.hpp>
#include <helper.hpp>
#include <iostream>

#include <components/position.hpp>
#include <components/renderable.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace jam {
using registry = entt::registry<uint32_t>;

void render(registry& reg, Renderer& renderer, shader::BasicShader& shader,
            glm::mat4& projection) {
  using namespace jam::component;
  shader.start();
  shader.loadProjection(projection);
  reg.view<Renderable, Position>().each(
      [&](auto entity, Renderable& rend, Position& pos) {
        glm::mat4 trans{1.0f};
        trans = glm::translate(trans, glm::vec3{pos.x, pos.y, pos.z});
        trans = glm::scale(trans, glm::vec3{50.0f});
        shader.loadModel(trans);
        renderer.render(rend.model);
      });

  shader.stop();
}

}  // namespace jam

int main() {
  auto window = jam::createWindow(1024.0f, 768.0f);

  jam::shader::BasicShader shader;
  jam::Renderer renderer;
  jam::Loader loader;

  auto model = jam::factory::rectangle(loader);

  glm::mat4 trans{1.0f};
  trans = glm::translate(
      trans, glm::vec3{window.width() / 2, window.height() / 2, 0.0f});
  trans = glm::scale(trans, glm::vec3{50.0f});

  glm::mat4 projection =
      glm::ortho(0.0f, window.width(), window.height(), 0.0f, -1.0f, 1.0f);

  jam::registry reg;
  auto entity1 = reg.create();
  reg.assign<jam::component::Position>(entity1, window.width() / 2,
                                       window.height() / 2, 0.0f);
  reg.assign<jam::component::Renderable>(entity1, model);

  auto entity2 = reg.create();
  reg.assign<jam::component::Position>(entity2, window.width() / 5,
                                       window.height() / 3, 0.0f);
  reg.assign<jam::component::Renderable>(entity2, model);

  auto entity3 = reg.create();
  reg.assign<jam::component::Position>(entity3, 100.0f, 2 * window.height() / 3,
                                       0.0f);
  reg.assign<jam::component::Renderable>(entity3, model);

  while (!window.shouldClose()) {
    renderer.newFrame();

    render(reg, renderer, shader, projection);

    window.pollEvents();
    window.swapBuffers();
    jam::mojave_fix(window);
  }
  return 0;
}
