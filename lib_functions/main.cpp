#include <emscripten.h>
#include <emscripten/bind.h>

void test_lib_functions();

template<typename T>
T* test_new();

void createInt() {
    int* pI = test_new<int>();
    *pI = 230204;
    printf("%d\n", *pI);
    delete pI;
}

void call_lib_functions()
{
    test_lib_functions();
    createInt();
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
}