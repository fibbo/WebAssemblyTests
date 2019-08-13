#include <emscripten/bind.h>
#include "side_api.h"
#include "simple_bse.h"
#include "main_api.h"

long CreateApiList_JS(int size) {
  printf("Creating Api List\n");
  return (long)::CreateApiList(size);
}

bool CloseList_JS(long list) {
  return ::CloseList((ConcreteApiObjectVector*)list);
}

EMSCRIPTEN_BINDINGS() {
  emscripten::function("CreateApiList", &CreateApiList_JS);
  emscripten::function("CloseList", &CloseList_JS);
}