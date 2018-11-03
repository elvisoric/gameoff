#ifndef JAM_FACTORY_HPP
#define JAM_FACTORY_HPP

#include <core/loader.h>
#include <core/raw_model.hpp>
#include <vector>

namespace jam {
namespace factory {
inline RawModel rectangle(Loader& loader) {
  std::vector<float> vertices = {// positions
                                 1.0f,  1.0f,  0.0f, 1.0f,  -1.0f, 0.0f,
                                 -1.0f, -1.0f, 0.0f, -1.0f, 1.0f,  0.0f};
  std::vector<unsigned int> indices = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };
  std::vector<float> dummy;
  auto model = loader.loadVAO(vertices, dummy, dummy, indices);
  return model;
}
}  // namespace factory
}  // namespace jam

#endif  // JAM_FACTORY_HPP