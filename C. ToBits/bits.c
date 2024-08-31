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

void toBits(void* data, size_t size, char* str)
{
    char* valueByte = beginByte(data, size);
    char* endingByte = endByte(data, size);
    for(size_t i = 0; valueByte != endingByte; valueByte += BIGENDIAN ? 1 : -1)
    {
        charToBits(*valueByte, str);
        str[++i * 9 - 1] = ' ';
    }
    str[size*9 -1] = 0;
}