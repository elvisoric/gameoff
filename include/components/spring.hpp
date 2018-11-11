#ifndef JAM_COMPONENTS_SPRING_HPP
#define JAM_COMPONENTS_SPRING_HPP

#include <glm/glm.hpp>

namespace jam {
namespace component {
struct Spring {
  glm::vec3 point;
  float k;
};
}  // namespace component
}  // namespace jam
#endif  // JAM_COMPONENTS_SPRING_HPP