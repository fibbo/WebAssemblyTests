#include "header.h"

extern void setBoolToFalse(DataStruct& ds);
extern DataStruct* createDataStruct();

void fillDataStructure(DataStruct& ds)
{
    for (int i = 0; i < ds.length; i++)
    {
        ds.bitmap[i] = i % 256;
    }
    setBoolToFalse(ds);
}

    
DataStruct* getDataStructureFromModule()
{
    return createDataStruct();
}