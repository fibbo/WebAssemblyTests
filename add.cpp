#include <emscripten.h>
// #include "emscripten/bind.h"
extern "C" {

void add(float* array, int length)
{
    for (int i = 0; i < length; i++)
    {
        array[i] += 2;
    }    
}

}

// EMSCRIPTEN_BINDINGS() {
//     function("multiply", &multiplyJS);
// }
