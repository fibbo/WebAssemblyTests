void setBufferData(long handle, int length)
{
    unsigned char* data = (unsigned char*) handle;
    for (int i = 0; i<length; i++)
    {
        data[i] = 200+i;
    }
}

int sidey()
{
    return 99;
}
