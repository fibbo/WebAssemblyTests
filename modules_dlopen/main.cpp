
#include <cstdio>
#include "header.h"
#include <dlfcn.h>

#include <emscripten.h>
#include <emscripten/bind.h>

typedef void (*fillPtr)(DataStruct& ds);

fillPtr dynLinkedFunc;
void* libhandle;

void loadDLL(std::string path)
{
    libhandle = dlopen(path.c_str(), RTLD_NOW);
    if (libhandle == nullptr)
        printf("Failed to load %s: %s\n", path.c_str(), dlerror());

    dynLinkedFunc = (fillPtr)dlsym(libhandle, "fillDataStructure");
    if (dynLinkedFunc == nullptr)
        printf("Failed to load function: %s\n", "fillDataStructure");
}

void interFunctionCallsDlopen(int size, std::string path)
{
    DataStruct ds;
    ds.is_knockout = true;
    ds.bitmap = new unsigned char[size];
    ds.length = size;

    if (!libhandle)
        loadDLL(path);

    dynLinkedFunc(ds);

    for (int i = 0; i < ds.length; i++)
    {
        printf("ds.bitmap[%d]: %d\n", i, ds.bitmap[i]);
    }

    printf("ds.is_knockout: %d\n", ds.is_knockout);
    delete[] ds.bitmap;
    ds.bitmap = nullptr;
}

void interFunctionCallAgain(int size)
{
    DataStruct ds;
    ds.is_knockout = true;
    ds.bitmap = new unsigned char[size];
    ds.length = size;

    assert(libhandle);

    dynLinkedFunc(ds);

    for (int i = 0; i < ds.length; i++)
    {
        printf("ds.bitmap[%d]: %d\n", i, ds.bitmap[i]);
    }

    printf("ds.is_knockout: %d\n", ds.is_knockout);
    delete[] ds.bitmap;
    ds.bitmap = nullptr;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}

EMSCRIPTEN_BINDINGS() {
    emscripten::function("interFunctionCallsDlopen", &interFunctionCallsDlopen);
    emscripten::function("interFunctionCallAgain", &interFunctionCallAgain);
}
