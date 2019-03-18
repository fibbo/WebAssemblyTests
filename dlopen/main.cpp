
#include <cstdio>
#include "../header.h"
#include <dlfcn.h>

#include <emscripten.h>
#include <emscripten/bind.h>

typedef DataStruct* (*getDataStructureFromModulePtr)();
typedef void (*deleteDataStructurePtr)(DataStruct*);
typedef double (*calcAverageModulePtr)(std::vector<double>&);
typedef PointFactory (*getPointFactoryPtr)();
typedef Point&& (*getPointPtr)(PointFactory&);
typedef std::vector<double> (*DistanceBetweenNeighborsModulePtr)(std::vector<Point>&);
typedef void (*modulePrintPtr)();
typedef float (*Return10Ptr)();

typedef Point (*MakePointPtr)();
typedef void (*PassVectorFloatPtr)(std::vector<float>&);
typedef std::vector<float> (*ReturnVectorFloatPtr)();

void* libhandle;
getDataStructureFromModulePtr GetDataStructureFromModule;
deleteDataStructurePtr DeleteDataStructure;
calcAverageModulePtr CalcAverageModule;
getPointFactoryPtr GetPointFactory;
getPointPtr GetPoint;
DistanceBetweenNeighborsModulePtr DistanceBetweenNeighborsModule;
modulePrintPtr ModulePrint;

void loadDLL(std::string path)
{
    libhandle = dlopen(path.c_str(), RTLD_NOW);
    if (libhandle == nullptr)
        printf("Failed to load %s: %s\n", path.c_str(), dlerror());

    GetDataStructureFromModule = (getDataStructureFromModulePtr)dlsym(libhandle, "GetDataStructureFromModule");
    if (GetDataStructureFromModule == nullptr)
        printf("Failed to load function: %s\n", "GetDataStructureFromModule");
    
    DeleteDataStructure = (deleteDataStructurePtr)dlsym(libhandle, "DeleteDataStructure");
    if (DeleteDataStructure == nullptr)
        printf("Failed to load function: %s\n", "DeleteDataStructure");

    CalcAverageModule = (calcAverageModulePtr)dlsym(libhandle, "CalcAverageModule");
    if (CalcAverageModule == nullptr)
        printf("Failed to load function: %s\n", "CalcAverageModule");

    GetPointFactory = (getPointFactoryPtr)dlsym(libhandle, "GetPointFactory");
    if (GetPointFactory == nullptr)
        printf("Failed to load function: %s\n", "GetPointFactory");

    GetPoint = (getPointPtr)dlsym(libhandle, "GetPoint");
    if (GetPoint == nullptr)
        printf("Failed to load function: %s\n", "GetPoint");

    DistanceBetweenNeighborsModule = (DistanceBetweenNeighborsModulePtr)dlsym(libhandle, "DistanceBetweenNeighborsModule");
    if (DistanceBetweenNeighborsModule == nullptr)
        printf("Failed to load function: %s\n", "DistanceBetweenNeighborsModule");
}

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
    EM_ASM_TIME('NewDeleteMainModule');
    for(size_t i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = new DataStruct;
        delete ds;
    }
    EM_ASM_TIMEEND('NewDeleteMainModule');

}

/**
 * Call 'new' in side module
 * Call 'delete' in side module
 */
void NewDeleteSideModule()
{
    EM_ASM_TIME('NewDeleteSideModule');
    for(size_t i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = GetDataStructureFromModule();
        DeleteDataStructure(ds);
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
    for(size_t i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = new DataStruct;
        DeleteDataStructure(ds);
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
    for(size_t i = 0; i < SAMPLE; i++)
    {
        DataStruct* ds = GetDataStructureFromModule();
        delete ds;
    }
    EM_ASM_TIMEEND('NewSideDeleteMainModule');
}

// Distance^2 between two points
float calcDistance2(const Point& p1, const Point& p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

std::vector<float> DistanceBetweenNeighbors(std::vector<Point>& points)
{
    std::vector<float> distances;
    for (size_t i = 1; i < points.size(); i++)
    {
        distances.push_back(calcDistance2(points[i-1], points[i]));
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
    distances = DistanceBetweenNeighbors(points);
    EM_ASM_TIMEEND("calcDistance");

    EM_ASM_TIME("calcAverage");
    printf("average distance between 2 points: %f\n", calcAverage(distances));
    EM_ASM_TIMEEND("calcAverage");

    EM_ASM_TIMEEND("pointTest");
}

void PointTestAcrossModule()
{
    PointFactory pf = GetPointFactory();
    std::vector<Point> points;
    printf("#####PointTests Across Modules\n");
    
    EM_ASM_TIME("pointTest");
    
    EM_ASM_TIME("createPoints");
    for(int i = 0; i < SAMPLE; i++)
    {
        points.emplace_back(GetPoint(pf));
    }
    EM_ASM_TIMEEND("createPoints");

    EM_ASM_TIME("calcDistance");
    std::vector<double> distances;
    distances = DistanceBetweenNeighborsModule(points);
    EM_ASM_TIMEEND("calcDistance");
    printf("%f\n", distances[0]);

    EM_ASM_TIME("calcAverage");
    printf("average distance between 2 points: %f\n", CalcAverageModule(distances));
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

EMSCRIPTEN_BINDINGS() {
    emscripten::function("loadDLL", &loadDLL);

    emscripten::function("setSampleCount", &setSampleCount);

    emscripten::function("NewDeleteMainModule", &NewDeleteMainModule);
    emscripten::function("NewDeleteSideModule", &NewDeleteSideModule);
    emscripten::function("NewMainDeleteSideModule", &NewMainDeleteSideModule);
    emscripten::function("NewSideDeleteMainModule", &NewSideDeleteMainModule);

    emscripten::function("PointTestAcrossModule", &PointTestAcrossModule);
    emscripten::function("PointTestWithinModule", &PointTestWithinModule);

    emscripten::function("useClassFromModule", &useClassFromModule);
}