#ifndef JAM_COMPONENTS_VELOCITY_HPP
#define JAM_COMPONENTS_VELOCITY_HPP

#include <glm/glm.hpp>

namespace jam {
namespace component {
struct Velocity {
  glm::vec3 dvec;
  float friction;
};
}  // namespace component
}  // namespace jam
#endif  // JAM_COMPONENTS_VELOCITY_HPP