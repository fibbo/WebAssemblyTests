#include <emscripten/bind.h>

using namespace emscripten;
#include <cstdio>
extern void setBufferData(long handle, int length);

int main()
{
    printf("Hello world!\n");
    return 0;
}

void mainSetBufferData(long handle, int length)
{
    setBufferData(handle, length);
}


EMSCRIPTEN_BINDINGS() {
    function("SetBufferData", &mainSetBufferData);
}