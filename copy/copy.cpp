#include <emscripten.h>
#include "emscripten/bind.h"
using namespace emscripten;

emscripten::val initVector(emscripten::val vector)
{
    std::vector<unsigned char> vec = vector.isNull() ? std::vector<unsigned char>() : emscripten::vecFromJSArray<unsigned char>(vector);
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] = 23+i;
    }
    emscripten::val value = emscripten::val::array();
    for (size_t i = 0; i < vec.size(); ++i)
        value.set(i, vec[i]);
    return value;
}

/*
    pass emscripten buffer to the function
*/
void initBuffer(long handle, int size)
{
    unsigned char* buffer = (unsigned char*)handle;
    for (int i = 0; i < size; i++)
    {
        buffer[i] = 48+i;
    }
}

EMSCRIPTEN_BINDINGS() {
    emscripten::function("initVector", &initVector);
    emscripten::function("initBuffer", &initBuffer);
}