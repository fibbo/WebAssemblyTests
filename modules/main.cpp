#include <emscripten.h>
#include "emscripten/bind.h"
using namespace emscripten;

#include <cstdio>

int main()
{
    printf("Hello world!\n");
    return 0;
}
