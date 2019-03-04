
#include <cstdio>
#include <iostream>
#include <vector>

#include <dlfcn.h>
#include "header.h"

#include <emscripten.h>
#include <emscripten/bind.h>

extern void fillDataStructure(DataStruct& ds);
extern DataStruct* getDataStructureFromModule();
extern void deleteDataStructure(DataStruct* ds);
extern float calcDistance2Module(const Point& p1, const Point& p2);
extern float calcAverageModule(const std::vector<float>& distances);
extern PointFactory getPointFactory();
extern Point&& getPoint(PointFactory& pf);
extern std::vector<float> getDistancesModule(std::vector<Point>& points);

int SAMPLE = 6000000;


void setSampleCount(int count)
{
    SAMPLE = count;
}

void runDataStructureTestAcrossModules()
{
    EM_ASM_TIME('acrossModule');
    for(size_t i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = getDataStructureFromModule();
        delete ds;
    }
    EM_ASM_TIMEEND('acrossModule');
}

void runDataStructureTestWithinModule()
{
    EM_ASM_TIME('withinModule');
    for(size_t i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = new DataStruct;
        delete ds;
    }
    EM_ASM_TIMEEND('withinModule');

}

float calcDistance2(const Point& p1, const Point& p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

std::vector<float> getDistances(std::vector<Point> points)
{
    std::vector<float> distances;
    printf("calculating distances in main module\n");
    for (size_t i = 1; i < points.size(); i++)
    {
        distances.push_back(calcDistance2Module(points[i-1], points[i]));
    }
    return distances;
}

float calcAverage(const std::vector<float>& distances)
{
    float sum = 0;
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
        points.emplace_back(pf.createPoint());
    }
    EM_ASM_TIMEEND("createPoints");

    EM_ASM_TIME("calcDistance");
    std::vector<float> distances;
    for (int i = 1; i<SAMPLE; i++)
    {
        distances.push_back(calcDistance2(points[i-1], points[i]));
    }
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
        points.emplace_back(getPoint(pf));
    }
    EM_ASM_TIMEEND("createPoints");
    EM_ASM_TIME("calcDistance");

    std::vector<float> distances;
    distances = getDistancesModule(points);
    EM_ASM_TIMEEND("calcDistance");

    EM_ASM_TIME("calcAverage");
    printf("average distance between 2 points: %f\n", calcAverageModule(distances));
    EM_ASM_TIMEEND("calcAverage");
    EM_ASM_TIMEEND("pointTest");
}

void useClassFromModule()
{
    ModuleClass c{"custom text", 99};
    c.print();
}


EMSCRIPTEN_BINDINGS() {
    emscripten::function("setSampleCount", &setSampleCount);
    emscripten::function("runDataStructureTestWithinModule", &runDataStructureTestWithinModule);
    emscripten::function("runDataStructureTestAcrossModules", &runDataStructureTestAcrossModules);
    emscripten::function("PointTestAcrossModule", &PointTestAcrossModule);
    emscripten::function("PointTestWithinModule", &PointTestWithinModule);

    emscripten::function("useClassFromModule", &useClassFromModule);
}
