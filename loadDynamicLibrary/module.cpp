#include <vector>
#include <cstdlib>
#include <utility>
#include <iostream>

#include "../header.h"

// defined in module2.cpp
extern void setBoolToFalse(DataStruct& ds);

// 'New' in module.cpp    
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

Point getPoint(PointFactory& pf)
{
    return pf.createPoint();
}

double calcDistance2Module(const Point& p1, const Point& p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

std::vector<double> DistanceBetweenNeighborsModule(std::vector<Point>& points)
{
    std::vector<double> distances;
    for (size_t i = 1; i < points.size(); i++)
    {
        distances.push_back(calcDistance2Module(points[i-1], points[i]));
    }
    return distances;
}

double calcAverageModule(const std::vector<double>& distances)
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