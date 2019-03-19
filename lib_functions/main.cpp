#include <iostream>

#include <emscripten.h>
#include <emscripten/bind.h>

void test_lib_functions();

double* new_double(int size);   

void call_lib_functions()
{
    test_lib_functions();
}

void call_side_new()
{
    std::cout << "call_side_new\n";
    double* pD = new_double(9999999);
    int dummy = 0;
    for (int i = 0; i < 9999999; i++)
    {
        dummy += pD[i];
    }
    std::cout << dummy << "\n";
}

void call_new()
{
    double* pD = new double[1];
    std::cout << pD[0] << "\n";
}

void loadLib()
{
    EM_ASM({
        loadDynamicLibrary('output/module.wasm', {loadAsync: true, global: true, nodelete: true}).then( () => { console.log('ole'); Module.loadedSideModule() } )
    });
}

EMSCRIPTEN_BINDINGS() {
    emscripten::function("loadLib", &loadLib);
    emscripten::function("lib_functions", &call_lib_functions);
    emscripten::function("call_new", &call_new);
    emscripten::function("call_side_new", &call_side_new);
}