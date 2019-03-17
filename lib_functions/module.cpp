#include <cstdlib>
#include <cstring>
#include <cstdio>

void test_lib_functions() {
    printf("Allocating\n");
    void* dst = malloc(12);
    const char text[12] = "I like food";

    printf("copying to dst\n");
    memcpy(dst, text, 12);
    printf("%s\n", dst);
    printf("freeing buffer\n");
    free(dst);
}

template<typename T>
T* test_new() {
    return new T;
}

template int* test_new<int>();