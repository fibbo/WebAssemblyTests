#include "emscripten/bind.h"
#include <emscripten.h>

using namespace emscripten;

int fib() {
  return 42;
}

EMSCRIPTEN_BINDINGS(test) {
    function("fiba", &fib);
}
