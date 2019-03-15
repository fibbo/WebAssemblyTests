#include <vector>
#include <cstdlib>
#include <utility>
#include <iostream>

#include "header.h"
// defined in module2.cpp
extern void setBoolToFalse(DataStruct& ds);

extern "C" {
// 'New' in module.cpp    
DataStruct* GetDataStructureFromModule()
{
    return new DataStruct();
}

void DeleteDataStructure(DataStruct* ds)
{
    delete ds;
}

PointFactory GetPointFactory()
{
    return PointFactory();
}

Point&& GetPoint(PointFactory& pf)
{
    return std::move(pf.createPoint());
}

double CalcDistance2Module(const Point& p1, const Point& p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

std::vector<double> DistanceBetweenNeighborsModule(std::vector<Point>& points)
{
    std::vector<double> distances;
    for (size_t i = 1; i < points.size(); i++)
    {
        distances.push_back(CalcDistance2Module(points[i-1], points[i]));
    }
    return distances;
}

double CalcAverageModule(std::vector<double>& distances)
{
    double sum = 0;
    for (auto d : distances)
    {
        sum += d;
    }
    return sum/distances.size();
}

/**
 * Implementation of the the class function print
 * Useable from the main_module
 */
void ModuleClass::print()
{
    std::cout << text << "\t" << value << "\n";
}


}
