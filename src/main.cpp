#include <window.h>
#include <entt.hpp>

namespace jam {
using registry = entt::registry<std::uint32_t>;
}

int main() {
  auto window = jam::createWindow(1024.0f, 768.0f);

  while (!window.shouldClose()) {
    window.pollEvents();
    window.swapBuffers();
  }
  return 0;
}
