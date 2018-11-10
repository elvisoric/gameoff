#ifndef JAM_UTIL_UTIL_HPP
#define JAM_UTIL_UTIL_HPP

#include <algorithm>
#include <components/collision.hpp>
#include <components/position.hpp>
#include <random>

namespace jam {

struct Rect {
  float x, y, width, height;
};

namespace util {

bool inRange(float value, float min, float max) {
  return value >= min && value <= max;
}

bool pointInRect(float x, float y, const component::Position& pos,
                 const component::Collision& col) {
  Rect r;
  r.x = pos.p.x;
  r.y = pos.p.y;
  r.width = col.width;
  r.height = col.height;
  return inRange(x, r.x, r.x + r.width) && inRange(y, r.y, r.y + r.height);
}

bool rangeInersect(float min0, float max0, float min1, float max1) {
  return std::max(min0, max0) >= std::min(min1, max1) &&
         std::min(min0, max0) <= std::max(min1, max1);
}

bool collide(const jam::Rect& r1, const jam::Rect& r2) {
  return rangeInersect(r1.x, r1.x + r1.width, r2.x, r2.x + r2.width) &&
         rangeInersect(r1.y, r1.y + r1.height, r2.y, r2.y + r2.height);
}

struct Random {
  Random(float from, float to) : mt{rd()}, dist{from, to} {}
  float operator()() { return dist(mt); }
  std::random_device rd;
  std::mt19937 mt;
  std::uniform_real_distribution<float> dist;
};
}  // namespace util
}  // namespace jam
#endif  // JAM_UTIL_UTIL_HPP