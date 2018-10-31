#include <entt.hpp>
#include <iostream>

namespace jam {
using registry = entt::registry<std::uint32_t>;
}

struct position {
  float x;
  float y;
};

struct velocity {
  float dx, dy;
};

int main() {
  jam::registry registry;
  auto entity = registry.create();

  std::cout << "Entity identifier: " << entity << std::endl;
  auto b = registry.valid(entity);
  if (b)
    std::cout << "Valid" << std::endl;
  else
    std::cout << "Not Valid " << std::endl;

  registry.assign<position>(entity, 3.0f, 2.0f);
  registry.assign<velocity>(entity);

  if (registry.has<position>(entity)) {
    std::cout << "Entity has position..." << std::endl;
  }

  if (registry.has<position, velocity>(entity)) {
    std::cout << "Entity has position and velocity ..." << std::endl;
  }

  const auto& pos = registry.get<position>(entity);
  auto& vel = registry.get<velocity>(entity);
  vel.dx = 32.0f;
  vel.dy = 22.2f;
  std::cout << "X: " << pos.x << " "
            << "Y: " << pos.y << std::endl;
  const auto& [cpos, cvel] = registry.get<position, velocity>(entity);

  std::cout << "X: " << cpos.x << " "
            << "Y: " << cpos.y << std::endl;

  std::cout << "dx: " << cvel.dx << " "
            << "dy: " << cvel.dy << std::endl;

  registry.destroy(entity);

  b = registry.valid(entity);
  if (b)
    std::cout << "Valid" << std::endl;
  else
    std::cout << "Not Valid " << std::endl;
  return 0;
}
