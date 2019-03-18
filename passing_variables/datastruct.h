#include <string>

struct DataStruct
{
    int x;
    int y;
    std::string text;
    void print()
    {
        printf("x: %d y: %d text: %s\n", x, y, text.c_str());
    }
};
