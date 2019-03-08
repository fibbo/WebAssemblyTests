#include "header.h"


void setBoolToFalse(DataStruct& ds)
{
  ds.is_knockout = false;
}

class SidePointFactory {
public:
  SidePointFactory()
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