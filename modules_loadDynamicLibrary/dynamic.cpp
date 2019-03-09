#include <cstdio>
#include <vector>
#include <utility>

std::vector<double> getDoubleVector()
{
  std::vector<double> vec{1.2, 3.4, 4.5};
  printf("function in dynamic.cpp\n");
  for(auto d : vec)
  {
    printf("%f\n", d);
  }
  return vec;
}

std::vector<double>* getDoubleVectorPointer()
{
  std::vector<double>* vec = new std::vector<double>{1.5, 4.6, 7.8};
  printf("function in dynamic.cpp\n");
  for(auto d : *vec)
  {
    printf("%f\n", d);
  }
  return vec;
}
