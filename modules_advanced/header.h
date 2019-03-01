#if !defined(_HEADER_H_)
#define _HEADER_H_

struct DataStruct {
  bool is_knockout;
  unsigned char* bitmap;
  int length;
  DataStruct() : length(0), is_knockout(true), bitmap(nullptr) {}
};

#include <emscripten.h>
#define EM_ASM_TIME(name)       EM_ASM( \
                                console.time(name);\
                             )
#define EM_ASM_TIMEEND(name)    EM_ASM( \
                                console.timeEnd(name);\
                             )

#endif
