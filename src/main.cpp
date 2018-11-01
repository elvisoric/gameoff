#include <entt.hpp>
#include <iostream>

namespace jam {
using registry = entt::registry<std::uint32_t>;
}

int main() {
  jam::registry registry;
  auto entity = registry.create();
  std::cout << "Entity identifier: " << entity << std::endl;
  registry.destroy(entity);
  return 0;
}
