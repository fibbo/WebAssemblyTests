
#include <cstdio>
#include <iostream>
#include <vector>

#include <emscripten.h>
#include <emscripten/bind.h>

#include "../header.h"
// #include "bsecoll.h"


// Definitions from other modules
extern DataStruct* getDataStructureFromModule();
extern void deleteDataStructure(DataStruct* ds);
extern double calcDistance2Module(const Point& p1, const Point& p2);
extern double calcAverageModule(const std::vector<double>& distances);
extern PointFactory getPointFactory();
extern Point getPoint(PointFactory& pf);
extern std::vector<double> DistanceBetweenNeighborsModule(std::vector<Point>& points);

int SAMPLE = 6000000;


void setSampleCount(int count)
{
    SAMPLE = count;
}

/**
 * Call 'new' in main module
 * Call 'delete' in main module
 */

void NewDeleteMainModule()
{
    int dummy = 0;

    EM_ASM_TIME('NewDeleteMainModule');
    for(int i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = new DataStruct;
        dummy += (int)ds->is_knockout;
        delete ds;
    }
    std::cout << dummy << "\n";
    EM_ASM_TIMEEND('NewDeleteMainModule');
}

/**
 * Call 'new' in side module
 * Call 'delete' in side module
 */
void NewDeleteSideModule()
{
    EM_ASM_TIME('NewDeleteSideModule');
    for(int i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = getDataStructureFromModule();
        deleteDataStructure(ds);
    }
    EM_ASM_TIMEEND('NewDeleteSideModule');
}

/**
 * Mixed calls: 
 * Call 'new' in main module
 * Call 'delete' in side module
 */
void NewMainDeleteSideModule()
{
    EM_ASM_TIME('NewMainDeleteSideModule');
    for(int i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = new DataStruct;
        deleteDataStructure(ds);
    }
    EM_ASM_TIMEEND('NewMainDeleteSideModule');
}

/**
 * Mixed calls:
 * Call 'new' in side module
 * Call 'delete' in main module
 */
void NewSideDeleteMainModule()
{
    EM_ASM_TIME('NewSideDeleteMainModule');
    for(int i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = getDataStructureFromModule();
        delete ds;
    }
    EM_ASM_TIMEEND('NewSideDeleteMainModule');
}

// Distance^2 between two points
double calcDistance2(const Point& p1, const Point& p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

std::vector<double> DistanceBetweenNeighbors(std::vector<Point>& points)
{
    std::vector<double> distances;
    for (size_t i = 1; i < points.size(); i++)
    {
        distances.push_back(calcDistance2(points[i-1], points[i]));
    }
    return distances;
}

double calcAverage(const std::vector<double>& distances)
{
    double sum = 0;
    for (auto d : distances)
    {
        sum += d;
    }
    return sum/distances.size();
}


void PointTestWithinModule()
{
    PointFactory pf;
    std::vector<Point> points;
    printf("#####PointTests Within Main\n");

    EM_ASM_TIME("pointTest");
    
    EM_ASM_TIME("createPoints");
    for(int i = 0; i < SAMPLE; i++)
    {
        points.push_back(pf.createPoint());
    }
    EM_ASM_TIMEEND("createPoints");

    EM_ASM_TIME("calcDistance");
    std::vector<double> distances;
    distances = DistanceBetweenNeighbors(points);
    EM_ASM_TIMEEND("calcDistance");

    EM_ASM_TIME("calcAverage");
    printf("average distance between 2 points: %f\n", calcAverage(distances));
    EM_ASM_TIMEEND("calcAverage");

    EM_ASM_TIMEEND("pointTest");
}

void PointTestAcrossModule()
{
    PointFactory pf = getPointFactory();
    std::vector<Point> points;
    printf("#####PointTests Across Modules\n");
    
    EM_ASM_TIME("pointTest");
    
    EM_ASM_TIME("createPoints");
    for(int i = 0; i < SAMPLE; i++)
    {
        points.push_back(getPoint(pf));
    }
    EM_ASM_TIMEEND("createPoints");

    EM_ASM_TIME("calcDistance");
    std::vector<double> distances;
    distances = DistanceBetweenNeighborsModule(points);
    EM_ASM_TIMEEND("calcDistance");

    EM_ASM_TIME("calcAverage");
    printf("average distance between 2 points: %f\n", calcAverageModule(distances));
    EM_ASM_TIMEEND("calcAverage");

    EM_ASM_TIMEEND("pointTest");
}

/**
 * Class is implemented in side_module
 * main_module only loads header.
 */
void useClassFromModule()
{
    ModuleClass c{"custom text", 99};
    c.print();
}

// void buffer_test() {
//     CBasicArray<ModuleClass*> buffer;
//     buffer.Add(new ModuleClass);
//     for (int i = 0; i < buffer.GetSize(); i++)
//     {
//         printf("mem loc: %p\n", buffer[i]);
//     }
// }


EMSCRIPTEN_BINDINGS() {
    emscripten::function("setSampleCount", &setSampleCount);

    emscripten::function("NewDeleteMainModule", &NewDeleteMainModule);
    emscripten::function("NewDeleteSideModule", &NewDeleteSideModule);
    emscripten::function("NewMainDeleteSideModule", &NewMainDeleteSideModule);
    emscripten::function("NewSideDeleteMainModule", &NewSideDeleteMainModule);

    emscripten::function("PointTestAcrossModule", &PointTestAcrossModule);
    emscripten::function("PointTestWithinModule", &PointTestWithinModule);

    emscripten::function("useClassFromModule", &useClassFromModule);
    // emscripten::function("buffer_test", &buffer_test);
}
