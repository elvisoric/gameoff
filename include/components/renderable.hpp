#ifndef JAM_COMPONENTS_RENDERABLE_HPP
#define JAM_COMPONENTS_RENDERABLE_HPP

#include <core/raw_model.hpp>

namespace jam {
namespace component {
struct Renderable {
  RawModel model;
  float scaleX;
  float scaleY;
};
}  // namespace component
}  // namespace jam
#endif  // JAM_COMPONENTS_RENDERABLE_HPP
