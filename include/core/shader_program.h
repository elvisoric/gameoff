#ifndef JAM_CORE_SHADER_PROGRAM_H
#define JAM_CORE_SHADER_PROGRAM_H

#include <glm/glm.hpp>
#include <string>

namespace jam {
namespace shader {
class Program {
 public:
  Program(const std::string& vertex, const std::string& fragment);
  virtual ~Program();

  void loadUniform(unsigned int location, bool value) const;
  void loadUniform(unsigned int location, int value) const;
  void loadUniform(unsigned int location, float value) const;
  void loadUniform(unsigned int location, const glm::vec3& value) const;
  void loadUniform(unsigned int location, const glm::mat4& value) const;

  void start() const;
  void stop() const;

  unsigned int getUniformLocation(const std::string& name) const;
  virtual void getAllUniformLocations() = 0;

 protected:
  virtual void bindAttributes() = 0;
  void bindAttribute(int attribute, const std::string& name);
  void link() const;

 private:
  unsigned int id_;
  unsigned int vertexId_;
  unsigned int fragmentId_;
};
}  // namespace shader
}  // namespace jam
#endif  // JAM_CORE_SHADER_PROGRAM_H