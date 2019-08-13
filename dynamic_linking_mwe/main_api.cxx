#include <cstdio>
#include "main_api.h"
#include "emscripten.h"

bool LoadLibrary() {
  printf("LoadLibrary\n");
  EM_ASM({
      loadDynamicLibrary('output/side_module.wasm', {loadAsync: true, global: true, nodelete: true}).then(
          () => {
              console.log('side_module loaded.');
              Module.modulePromiseResolve();
          });
  });
  return true;
}

int main() {
  LoadLibrary();
}