#include <string>

struct DataStruct
{
    int x;
    int y;
    std::string text;
    void print()
    {
        printf("%d %d %s\n", x, y, text.c_str());
    }
};
