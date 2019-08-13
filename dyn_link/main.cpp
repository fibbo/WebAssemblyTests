#include "template_class.h"
#include <emscripten/bind.h>
#include "side.h"
#include <cstdio>


void use_template_from_main() {
  printf("use from main\n");
  vec<3, float> v;
  v.print();
}

void use_template_from_side() {
  printf("use from side\n");
  side_class s;
  s.call();
}


EMSCRIPTEN_BINDINGS() {
  emscripten::function("use_template_from_main", &use_template_from_main);
  emscripten::function("use_template_from_side", &use_template_from_side);
}