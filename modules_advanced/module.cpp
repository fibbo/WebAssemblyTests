#include <vector>
#include "header.h"
#include <cstdlib>
#include <utility>
#include <iostream>

// defined in module2.cpp
extern void setBoolToFalse(DataStruct& ds);

void fillDataStructure(DataStruct& ds)
{
    for (int i = 0; i < ds.length; i++)
    {
        ds.bitmap[i] = i % 256;
    }
    setBoolToFalse(ds);
}

// malloc in module.cpp    
DataStruct* getDataStructureFromModule()
{
    return new DataStruct();
}

void deleteDataStructure(DataStruct* ds)
{
    delete ds;
}

PointFactory getPointFactory()
{
    return PointFactory();
}

Point&& getPoint(PointFactory& pf)
{
    return pf.createPoint();
}

float calcDistance2Module(const Point& p1, const Point& p2)
{
    EM_ASM({
        console.log('shit doesnt work')
    });
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

std::vector<float> getDistancesModule(std::vector<Point>& points)
{
    std::vector<float> distances;
    printf("calculating distances in side module\n");
    for (size_t i = 1; i < points.size(); i++)
    {
        distances.push_back(calcDistance2Module(points[i-1], points[i]));
    }
    return distances;
}

float calcAverageModule(const std::vector<float>& distances)
{
    double sum = 0;
    for (auto d : distances)
    {
        sum += d;
    }
    return sum/distances.size();
}

void ModuleClass::print()
{
    std::cout << text << "\t" << value << "\n";
}