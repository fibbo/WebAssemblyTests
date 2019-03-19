#include <iostream>
#include <string>

class A {
  std::string m_text;
  int m_number;

  void print();
};


void A::print() {
  std::cout << m_text << " " << m_number << "\n";
}
