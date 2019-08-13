#include "side.h"
#include "template_class.h"
#include <emscripten/bind.h>


void use_template_from_side() {
  vec<3, float> f;
  f.print();
}

void side_class::call() {
  use_template_from_side();
}


