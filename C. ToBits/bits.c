#include "bits.h"
#include "endianness.h"

char* beginByte(void* data, size_t size)
{
    if (BIG_ENDIAN)
        return (char*) data;
    return (char*) data + size - 1;
}

char* endByte(void* data, size_t size)
{
    if (LITTLE_ENDIAN)
        return (char*) data - 1;
    return (char*) data + size;
}