#if !defined(_HEADER_H_)
#define _HEADER_H_

#include <random>
#include <utility>

struct Point {
  float x;
  float y;
};

struct DataStruct {
  int length;
  bool is_knockout;
  unsigned char* bitmap;
  Point* points;

  DataStruct() : length(0), is_knockout(true), bitmap(nullptr), points(nullptr) {}
  DataStruct(int l, bool k, size_t size_bitmap, size_t size_points) : length(l), is_knockout(k), bitmap(new unsigned char[size_bitmap]), points(new Point[size_points]) {}
  ~DataStruct()
  {
    if (bitmap) delete[] bitmap;
    if (points) delete[] points;
  }
};

class PointFactory {
public:
  PointFactory()
  {
    m_rng.seed(std::random_device()());
    m_dist = std::uniform_real_distribution<>(0, 1);
  }
  Point&& createPoint()
  {
    Point p;
    p.x = m_dist(m_rng);
    p.y = m_dist(m_rng);
    return std::move(p);
  }
private:
  std::mt19937 m_rng;
  std::uniform_real_distribution<> m_dist;
};


class ModuleClass {
public:
  ModuleClass() { text = "empty"; value = -1; }
  ModuleClass(std::string text, int value) : text(text), value(value) { }
  void print();
private:
  std::string text;
  int value;
};



#include <emscripten.h>
#define EM_ASM_TIME(name)       EM_ASM( \
                                console.time(name);\
                             )
#define EM_ASM_TIMEEND(name)    EM_ASM( \
                                console.timeEnd(name);\
                             )

#endif
