#include <iostream>
#include <cstdio>

template<size_t DIM, typename T>
class vec {
public:
  vec() {
    printf("vec constructor\n");
    for (int i = 0; i < DIM; data[i++] = T());
    printf("finished constructor\n");
  }

  void print() {
    for (size_t i = 0; i < DIM; i++)
    {
      std::cout << data[i] << "\n";
    }
    
  }


private:
  T data[DIM];
};