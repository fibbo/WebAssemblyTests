#include <dlfcn.h>
#include <cstdio>
#include <string>
#if defined (EMSCRIPTEN)
#include <emscripten.h>
#include <emscripten/bind.h>
#endif

typedef double (*ReturnFloatPtr)();

ReturnFloatPtr ReturnFloat;

void LoadDLL(std::string path) 
{
  void* libhandle = dlopen(path.c_str(), RTLD_NOW);
  if (libhandle == nullptr)
  {
    printf("failed to load library\n");
  }

  ReturnFloat = (ReturnFloatPtr)dlsym(libhandle, "ReturnFloat");
  if (ReturnFloat == nullptr)
  {
    printf("failed to get symbol adress\n");
  }
}


void ReturnFloatTest()
{
  double f = ReturnFloat();
  printf("%f\n", f);
  printf("%f\n", ReturnFloat());
}

#if !defined(EMSCRIPTEN)
int main()
{
    LoadDLL("module.dll");
    printf("%f\n", ReturnFloat());
}
#endif

#if defined(EMSCRIPTEN)
EMSCRIPTEN_BINDINGS() {
  emscripten::function("LoadDLL", &LoadDLL);
  emscripten::function("ReturnFloatTest", &ReturnFloatTest);
}
#endif
