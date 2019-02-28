#include <iostream>
#include <string>
#include <emscripten.h>
#include "emscripten/bind.h"
#include "datastruct.h"

using namespace emscripten;

class MyClass {
public:
  MyClass(int x, std::string y)
    : x(x)
    , y(y)
  {}

  void incrementX() {
    ++x;
  }

  int getX() const { return x; }
  void setX(int x_) { x = x_; }
  void print()
  {
    std::cout << x << "\t" << y << '\n';
  } 


  static std::string getStringFromInstance(const MyClass& instance) {
    return instance.y;
  }

private:
  int x;
  std::string y;
};

void setXRef(MyClass& c, int x)
{
    c.setX(x);
}

void setXNoRef(MyClass c, int x)
{
    c.setX(x);
}


void updateRefDataStruct(DataStruct& s)
{
    s.x = 1001;
    s.y = 1002;
    s.text = "updatedTextRef";
    s.print();
}

void updateNoRefDataStruct(DataStruct s)
{
    s.x = 7001;
    s.y = 7002;
    s.text = "updatedTextNoRef";   
    s.print();
}

// Binding code
EMSCRIPTEN_BINDINGS() {
  class_<MyClass>("MyClass")
    .constructor<int, std::string>()
    .function("incrementX", &MyClass::incrementX)
    .function("print", &MyClass::print)
    .property("x", &MyClass::getX, &MyClass::setX)
    .class_function("getStringFromInstance", &MyClass::getStringFromInstance)
    ;

    function("setXRef", &setXRef);
    function("setXNoRef", &setXNoRef);
    function("updateRefDataStruct", &updateRefDataStruct);
    function("updateNoRefDataStruct", &updateNoRefDataStruct);

    value_object<DataStruct>("DataStruct")
        .field("x", &DataStruct::x)
        .field("y", &DataStruct::y)
        .field("text", &DataStruct::text);
}