#include <entt.hpp>
#include <iostream>

int main() {
  entt::registry registry;
  auto entity = registry.create();
  std::cout << "Entity: " << entity << std::endl;
  registry.destroy(entity);
  return 0;
}