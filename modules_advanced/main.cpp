
#include <cstdio>

#include "header.h"

#include <emscripten.h>
#include <emscripten/bind.h>

extern void fillDataStructure(DataStruct& ds);

void interFunctionCalls(int sizeOfBitmap)
{
    DataStruct ds;
    ds.is_knockout = true;
    ds.bitmap = new unsigned char[sizeOfBitmap];
    ds.length = sizeOfBitmap;
    fillDataStructure(ds);

    for (int i = 0; i < ds.length; i++)
    {
        printf("ds.bitmap[%d]: %d\n", i, ds.bitmap[i]);
    }

    printf("ds.is_knockout: %d\n", ds.is_knockout);
}

int main()
{
    printf("Hello world!\n");
    return 0;
}

EMSCRIPTEN_BINDINGS() {
    emscripten::function("interFunctionCalls", &interFunctionCalls);
}