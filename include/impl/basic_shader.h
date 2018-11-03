#ifndef JAM_IMPL_SHADER_BASIC_SHADER_H
#define JAM_IMPL_SHADER_BASIC_SHADER_H

#include <core/shader_program.h>

namespace jam {
namespace shader {
class BasicShader : public Program {
 public:
  BasicShader() : Program{"shaders/basic.vs", "shaders/basic.fs"} {}
  ~BasicShader() = default;

  void getAllUniformLocations() override {}

 protected:
  void bindAttributes() override {
    bindAttribute(0, "position");
    link();
    getAllUniformLocations();
  }

 private:
};
}  // namespace shader
}  // namespace jam
#endif  // JAM_IMPL_SHADER_BASIC_SHADER_H