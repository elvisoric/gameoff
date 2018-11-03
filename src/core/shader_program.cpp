#include <glad/glad.h>

#include <core/shader_program.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>

namespace {
std::string typeAsString(int type) {
  switch (type) {
    case GL_VERTEX_SHADER:
      return "VERTEX";
    case GL_FRAGMENT_SHADER:
      return "FRAGMENT";
    default:
      return "UNKNOWN";
  }
}
unsigned int loadShader(const std::string& file, int type) {
  std::string code;
  std::ifstream shaderFile;
  shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    shaderFile.open(file);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    code = shaderStream.str();
  } catch (std::ifstream::failure& f) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  const char* shaderCode = code.c_str();
  unsigned int shaderID;
  int success;
  char logInfo[512];

  shaderID = glCreateShader(type);
  glShaderSource(shaderID, 1, &shaderCode, NULL);
  glCompileShader(shaderID);
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shaderID, 512, NULL, logInfo);
    std::cout << file << std::endl;
    std::cout << "ERROR::SHADER::" << typeAsString(type)
              << "::COMPILE_ERROR: " << logInfo << std::endl;
  }
  return shaderID;
}
}  // namespace

namespace jam {
namespace shader {
Program::Program(const std::string& vertex, const std::string& fragment) {
  vertexId_ = loadShader(vertex, GL_VERTEX_SHADER);
  fragmentId_ = loadShader(fragment, GL_FRAGMENT_SHADER);
  id_ = glCreateProgram();
  glAttachShader(id_, vertexId_);
  glAttachShader(id_, fragmentId_);
}

Program::~Program() {
  stop();
  glDetachShader(id_, vertexId_);
  glDetachShader(id_, fragmentId_);
  glDeleteShader(vertexId_);
  glDeleteShader(fragmentId_);
}

void Program::start() const { glUseProgram(id_); }
void Program::stop() const { glUseProgram(0); }

void Program::link() const {
  glLinkProgram(id_);
  glValidateProgram(id_);
  int success;
  char logInfo[512];
  glGetProgramiv(id_, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id_, 512, NULL, logInfo);
    std::cout << "ERROR::PROGRAM::LINK_ERROR " << logInfo << std::endl;
  }
}

void Program::bindAttribute(int attribute, const std::string& name) {
  glBindAttribLocation(id_, attribute, name.c_str());
}

void Program::loadUniform(unsigned int location, bool value) const {
  float toLoad = 0.0f;
  if (value) toLoad = 1.0f;
  glUniform1f(location, value);
}

void Program::loadUniform(unsigned int location, int value) const {
  glUniform1i(location, value);
}

void Program::loadUniform(unsigned int location, float value) const {
  glUniform1f(location, value);
}

void Program::loadUniform(unsigned int location, const glm::vec3& value) const {
  glUniform3fv(location, 1, glm::value_ptr(value));
}

void Program::loadUniform(unsigned int location, const glm::mat4& value) const {
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

unsigned int Program::getUniformLocation(const std::string& uniformName) const {
  return glGetUniformLocation(id_, uniformName.c_str());
}

}  // namespace shader
}  // namespace jam