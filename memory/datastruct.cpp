#include "datastruct.h"

void updateRefDataStruct(DataStruct& s)
{
    s.x = 1001;
    s.y = 1002;
    s.text = "updatedTextRef";
    s.print();
}

void updateNoRefDataStruct(DataStruct s)
{
    s.x = 7001;
    s.y = 7002;
    s.text = "updatedTextNoRef";   
    s.print();
}
