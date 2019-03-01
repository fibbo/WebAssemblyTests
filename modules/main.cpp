#include <cstdio>

#include <emscripten.h>
#include <emscripten/bind.h>

extern int sidey();
extern void setBufferData(long, int);

void mainSetBufferData(long handle, int length)
{
    setBufferData(handle, length);
}

int main()
{
    printf("Hello world! %d \n", sidey());
    return 0;
}

EMSCRIPTEN_BINDINGS() {
    emscripten::function("setBufferData", &mainSetBufferData);
}
