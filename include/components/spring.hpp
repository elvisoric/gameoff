#ifndef JAM_COMPONENTS_SPRING_HPP
#define JAM_COMPONENTS_SPRING_HPP

#include <glm/glm.hpp>

namespace jam {
namespace component {
struct Spring {
  uint32_t other;
  float k;
  float length;
};
}  // namespace component
}  // namespace jam
#endif  // JAM_COMPONENTS_SPRING_HPP