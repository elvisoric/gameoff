#include <glad/glad.h>

#include <core/loader.h>
#include <core/renderer.h>
#include <impl/basic_shader.h>
#include <window.h>
#include <chrono>
#include <entt.hpp>
#include <factory.hpp>
#include <helper.hpp>
#include <iostream>
#include <thread>

#include <components/collision.hpp>
#include <components/position.hpp>
#include <components/renderable.hpp>
#include <components/velocity.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace std::chrono_literals;

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
        trans = glm::scale(trans, glm::vec3{30.0f});
        shader.loadModel(trans);
        renderer.render(rend.model);
      });

  shader.stop();
}

void move(registry& reg) {
  using namespace jam::component;
  reg.view<Position, Velocity>().each(
      [&](auto entity, Position& pos, Velocity& vel) {
        pos.x += vel.dvec.x;
        pos.y += vel.dvec.y;
        pos.z += vel.dvec.z;
      });
}

void collision(registry& reg, Window& window) {
  using namespace jam::component;
  // TODO: 30.0f is scale value. Need to improve this code to use scale
  // value instead of hard coded value.
  const auto scaleFactor = 30.0f;
  reg.view<Position, Velocity, Collision>().each(
      [&](auto entity, Position& pos, Velocity& vel, Collision&) {
        if (pos.x - scaleFactor <= 0.0f) {
          pos.x = 0.0f + scaleFactor;
          vel.dvec.x *= -1;
        } else if (pos.x + scaleFactor >= window.width()) {
          pos.x = window.width() - scaleFactor;
          vel.dvec.x *= -1;
        }
        if (pos.y - scaleFactor <= 0.0f) {
          pos.y = 0.0f + scaleFactor;
          vel.dvec.y *= -1;
        } else if (pos.y + scaleFactor >= window.height()) {
          pos.y = window.height() - scaleFactor;
          vel.dvec.y *= -1;
        }
      });
}

}  // namespace jam

namespace {
void prepare(jam::Window& window, jam::registry& reg, jam::Loader& loader) {
  auto model = jam::factory::rectangle(loader);
  auto entity1 = reg.create();
  reg.assign<jam::component::Position>(entity1, window.width() / 2,
                                       window.height() / 2, 0.0f);
  reg.assign<jam::component::Renderable>(entity1, model);
  reg.assign<jam::component::Velocity>(entity1, glm::vec3{3.0f, -4.0f, 0.0f});
  reg.assign<jam::component::Collision>(entity1);
}
}  // namespace

int main() {
  using clock = std::chrono::high_resolution_clock;
  auto window = jam::createWindow(1024.0f, 768.0f);

  jam::shader::BasicShader shader;
  jam::Renderer renderer;
  jam::Loader loader;

  glm::mat4 projection =
      glm::ortho(0.0f, window.width(), window.height(), 0.0f, -1.0f, 1.0f);

  jam::registry reg;
  prepare(window, reg, loader);

  std::chrono::nanoseconds perFrame = std::chrono::milliseconds{1000} / 70;
  while (!window.shouldClose()) {
    auto start = clock::now();
    renderer.newFrame();
    jam::move(reg);
    jam::collision(reg, window);
    jam::render(reg, renderer, shader, projection);

    window.pollEvents();
    window.swapBuffers();
    jam::mojave_fix(window);
    auto end = clock::now();

    std::chrono::nanoseconds sleepTime = end - start + perFrame;
    if (sleepTime > 0ns) {
      std::this_thread::sleep_for(sleepTime);
    } else {
      std::cout << "need to catch up here..." << std::endl;
    }
  }
  return 0;
}
