#include <emscripten.h>
#include "emscripten/bind.h"
using namespace emscripten;

emscripten::val setVectorData(emscripten::val vec)
{
    std::vector<double> vector = vec.isNull() ? std::vector<double>() : emscripten::vecFromJSArray<double>(vec);
    for (int i = 0; i < vector.size(); i++)
    {
        vector[i] = 3000+i;
    }
    return emscripten::val(vector);
}

void setBufferData(long handle, int length)
{
    unsigned char* data = (unsigned char*) handle;
    for (int i = 0; i<length; i++)
    {
        data[i] = 2000+i;
    }
}

EMSCRIPTEN_BINDINGS() {
    function("setVectorData", &setVectorData);
    function("setBufferData", &setBufferData);
}