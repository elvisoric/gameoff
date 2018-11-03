#include <core/loader.h>

#include <glad/glad.h>

namespace jam {

Loader::~Loader() { cleanUp(); }

RawModel Loader::loadVAO(std::vector<float> &vertices,
                         std::vector<float> &textureCoords,
                         std::vector<float> &normals,
                         std::vector<unsigned int> &indices) {
  auto vao = createVAO();
  storeDataInAttributesList(0, 3, vertices);
  // TODO: store textures and normals
  bindIndicesBuffer(indices);
  unbindVAO();
  return RawModel{vao, indices.size()};
}

void Loader::cleanUp() {
  for (auto &vao : vaos_) glDeleteVertexArrays(1, &vao);
  for (auto &vbo : vbos_) glDeleteBuffers(1, &vbo);
  for (auto &tex : textures_) glDeleteBuffers(1, &tex);
}
void Loader::unbindVAO() { glBindVertexArray(0); }
unsigned int Loader::createVAO() {
  unsigned int vao;
  vaos_.push_back(vao);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  return vao;
}

void Loader::storeDataInAttributesList(int attributeNumber,
                                       unsigned int coordinateSize,
                                       std::vector<float> &data) {
  unsigned int vbo;
  vbos_.push_back(vbo);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(),
               GL_STATIC_DRAW);
  glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE,
                        coordinateSize * sizeof(float), (void *)0);
  glEnableVertexAttribArray(attributeNumber);
}

void Loader::bindIndicesBuffer(std::vector<unsigned int> &indices) {
  unsigned int ebo;
  vbos_.push_back(ebo);
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
               indices.data(), GL_STATIC_DRAW);
}

unsigned int Loader::loadTexture(const std::string &path) { return 0; }
}  // namespace jam