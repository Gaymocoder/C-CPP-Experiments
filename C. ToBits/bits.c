#include "bits.h"
#include "endianness.h"

char* beginByte(void* data, size_t size)
{
    if (BIG_ENDIAN)
        return (char*) data;
    return (char*) data + size - 1;
}