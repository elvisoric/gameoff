#ifndef JAM_IMPL_SHADER_BASIC_SHADER_H
#define JAM_IMPL_SHADER_BASIC_SHADER_H

#include <core/shader_program.h>

namespace jam {
namespace shader {
class BasicShader : public Program {
 public:
  BasicShader() : Program{"shaders/basic.vs", "shaders/basic.fs"} {
    bindAttributes();
  }
  ~BasicShader() = default;

  inline void loadModel(const glm::mat4& model) const {
    loadUniform(modelLocation_, model);
  }

  inline void loadProjection(const glm::mat4& proj) const {
    loadUniform(projectionLocation_, proj);
  }

  inline void color(const glm::vec3& c) const {
    loadUniform(colorLocation_, c);
  }

  void getAllUniformLocations() override {
    modelLocation_ = getUniformLocation("model");
    projectionLocation_ = getUniformLocation("projection");
    colorLocation_ = getUniformLocation("color");
  }

 protected:
  void bindAttributes() override {
    bindAttribute(0, "position");
    link();
    getAllUniformLocations();
  }

 private:
  unsigned int modelLocation_;
  unsigned int projectionLocation_;
  unsigned int colorLocation_;
};
}  // namespace shader
}  // namespace jam
#endif  // JAM_IMPL_SHADER_BASIC_SHADER_H