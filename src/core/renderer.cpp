#include <glad/glad.h>

#include <core/renderer.h>
#include <core/raw_model.hpp>

namespace jam {
void Renderer::newFrame() {
  glClearColor(0.4f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::render(const RawModel& model) {
  glBindVertexArray(model.vaoID());
  glEnableVertexAttribArray(0);

  glDrawElements(GL_TRIANGLES, model.vertexCount(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
}
}  // namespace jam