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

#include <components/acceleration.hpp>
#include <components/collision.hpp>
#include <components/position.hpp>
#include <components/renderable.hpp>
#include <components/velocity.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <random>

#include <behavioral/observer.hpp>
#include <creational/singleton.hpp>
#include <util/util.hpp>

using namespace std::chrono_literals;

namespace jam {
using registry = entt::registry<uint32_t>;

using CursorSubject = patterns::behavioral::Subject<float, float>;
using CursorSingleton = patterns::creational::Singleton<CursorSubject>;

void render(registry& reg, Renderer& renderer, shader::BasicShader& shader,
            glm::mat4& projection) {
  using namespace jam::component;
  shader.start();
  shader.loadProjection(projection);
  reg.view<Renderable, Position>().each(
      [&](auto entity, Renderable& rend, Position& pos) {
        glm::mat4 trans{1.0f};
        trans = glm::translate(trans, pos.p);
        trans = glm::scale(trans, glm::vec3{rend.scaleX, rend.scaleY, 0.0f});
        shader.loadModel(trans);
        shader.color(rend.color);
        renderer.render(rend.model);
      });

  shader.stop();
}

void acceleration(registry& reg) {
  using namespace jam::component;
  reg.view<Velocity, Acceleration>().each(
      [&](auto entity, Velocity& vel, Acceleration& acc) {
        vel.dvec += acc.vec;
      });
}
void move(registry& reg) {
  using namespace jam::component;
  reg.view<Position, Velocity>().each(
      [&](auto entity, Position& pos, Velocity& vel) {
        pos.p += vel.dvec;
        vel.dvec *= vel.friction;
      });
}

void collision(registry& reg, Window& window) {
  using namespace jam::component;
  reg.view<Position, Velocity, Collision>().each([&](auto entity, Position& pos,
                                                     Velocity& vel,
                                                     Collision& col) {
    if (pos.p.x - col.width / 2 <= 0.0f) {
      pos.p.x = col.width / 2;
      vel.dvec.x *= -1;
    } else if (pos.p.x + col.width / 2 >= window.width()) {
      pos.p.x = window.width() - col.width / 2;
      vel.dvec.x *= -1;
    }
    if (pos.p.y - col.height / 2 <= 0.0f) {
      pos.p.y = col.height / 2;
      vel.dvec.y *= -1;
    } else if (pos.p.y + col.height / 2 >= window.height()) {
      pos.p.y = window.height() - col.height / 2;
      vel.dvec.x = 0.0f;
      vel.dvec.y = 0.0f;
    }

    reg.view<Position, Collision, Renderable>().each(
        [&](auto e, Position& p, Collision& c, Renderable& r) {
          Rect r1{p.p.x - c.width / 2, p.p.y - c.height / 2, c.width, c.height};
          Rect r2{pos.p.x - col.width / 2, pos.p.y - col.height / 2, col.width,
                  col.height};
          if (e != entity) {
            if (jam::util::collide(r1, r2)) {
              r.color = glm::vec3{1.0f, 0.0f, 0.0f};
              vel.dvec.x = 0.0f;
              vel.dvec.y = 0.0f;
              vel.friction = 1.0f;
              if (reg.has<Acceleration>(entity)) {
                auto& a = reg.get<Acceleration>(entity);
                a.vec = glm::vec3{0.0f};
              }
            }
          }
        });
  });
}

}  // namespace jam

namespace {

void entities(jam::registry& reg, jam::Loader& loader) {
  auto model = jam::factory::rectangle(loader);
  jam::util::Random r{2.0f, 50.0f};
  jam::util::Random rv{-8.0f, 8.0f};
  jam::util::Random rc{0.0f, 1.0f};
  jam::util::Random rwidth{30.0f, 100.0f};
  jam::util::Random rheight{50.0f, 100.0f};
  jam::util::Random pwidth{0.0f, 1000.0f};
  jam::util::Random pheight{0.0f, 800.0f};
  for (int i = 0; i < 20; ++i) {
    auto entity = reg.create();
    float width = rwidth();
    float height = rheight();
    reg.assign<jam::component::Position>(entity,
                                         glm::vec3{pwidth(), pheight(), 0.0f});
    reg.assign<jam::component::Renderable>(entity, model, width / 2, height / 2,
                                           glm::vec3{rc(), rc(), rc()});
    reg.assign<jam::component::Velocity>(entity, glm::vec3{rv(), -rv(), 0.0f},
                                         1.0f);
    reg.assign<jam::component::Acceleration>(entity,
                                             glm::vec3{0.0f, 0.13f, 0.0f});
    reg.assign<jam::component::Collision>(entity, width, height);
  }
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
  entities(reg, loader);

  std::chrono::nanoseconds perFrame = std::chrono::milliseconds{1000} / 70;
  while (!window.shouldClose()) {
    auto start = clock::now();
    renderer.newFrame();
    jam::acceleration(reg);
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
