
#include <cstdio>
#include <dlfcn.h>
#include "header.h"

#include <emscripten.h>
#include <emscripten/bind.h>

extern void fillDataStructure(DataStruct& ds);
extern DataStruct* getDataStructureFromModule();

constexpr int SAMPLE = 100000000;


void loadLib(std::string libname)
{
    dlopen(libname.c_str(), RTLD_NOW);
}
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
    delete[] ds.bitmap;
    ds.bitmap = nullptr;
}

void runDataStructureTestAcrossModules()
{
    EM_ASM_TIME('acrossModule');
    for(size_t i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = getDataStructureFromModule();
        // printf("%d\n", ds->length);
        delete ds;
    }
    EM_ASM_TIMEEND('acrossModule');
}

void runDataStructureTestWithinModule()
{
    EM_ASM_TIME('withinModule');
    for(size_t i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = new DataStruct;
        // printf("%d\n", ds->length);
        delete ds;
    }
    EM_ASM_TIMEEND('withinModule');

}

DataStruct* createDataStruct()
{
    return new DataStruct;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}

EMSCRIPTEN_BINDINGS() {
    emscripten::function("interFunctionCalls", &interFunctionCalls);
    emscripten::function("runDataStructureTestWithinModule", &runDataStructureTestWithinModule);
    emscripten::function("runDataStructureTestAcrossModules", &runDataStructureTestAcrossModules);
    emscripten::function("loadLib", &loadLib);
}
