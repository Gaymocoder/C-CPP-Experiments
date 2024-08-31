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

void charToBits(char value, char* str)
{
    for(uint8_t = 0; i < 8; ++i)
    {
        if (value & (1 << (8 - i - 1)))
            str[i + i/8] = '1';
        else
            str[i + i/8] = '0';
    }
}