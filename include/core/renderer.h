#ifndef JAM_CORE_RENDERER_H
#define JAM_CORE_RENDERER_H
namespace jam {
class RawModel;
class Renderer {
 public:
  Renderer() = default;
  void newFrame();
  void render(const RawModel& model);

 private:
};

}  // namespace jam
#endif  // JAM_CORE_RENDERER_H