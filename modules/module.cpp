#ifdef _WIN32
#  define EXPORT __declspec(dllexport)
#  define IMPORT __declspec(dllimport)
#else
#  define EXPORT __attribute__ ((visibility ("default")))
#  define IMPORT __attribute__ ((visibility ("default")))
#endif

EXPORT void setBufferData(long handle, int length)
{
    unsigned char* data = (unsigned char*) handle;
    for (int i = 0; i<length; i++)
    {
        data[i] = 2000+i;
    }
}

EXPORT int sidey()
{
    return 23;
}
