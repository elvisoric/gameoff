#ifndef JAM_CORE_RAW_MODEL_HPP
#define JAM_CORE_RAW_MODEL_HPP

namespace jam {
class RawModel {
 public:
  RawModel() = default;
  RawModel(unsigned int vaoID, unsigned long vertexCount)
      : vaoID_{vaoID}, vertexCount_{vertexCount} {}
  inline unsigned int vaoID() const { return vaoID_; }
  inline unsigned long vertexCount() const { return vertexCount_; }

 private:
  unsigned int vaoID_;
  unsigned long vertexCount_;
};
}  // namespace jam
#endif  // JAM_CORE_RAW_MODEL_HPP