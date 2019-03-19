#include <iostream>

#include <emscripten.h>
#include <emscripten/bind.h>

double* new_double(int);

int main()
{
  volatile double* a = new double[12];
  for (int i = 0; i< 12; i++)
  {
    std::cout << i[a] << "\n";
  }
}

void call()
{
  double* d = new_double(25);
  for (int i = 0; i<25; i++)
  {
    std::cout << d[i] << "\n";
  }
}

void loadLib()
{
    EM_ASM({
        loadDynamicLibrary('output/module.wasm', {loadAsync: true, global: true, nodelete: true}).then( () => { Module.loadedSideModule() } )
    });
}

EMSCRIPTEN_BINDINGS() {
  emscripten::function("loadLib", &loadLib);
  emscripten::function("call", &call);
}