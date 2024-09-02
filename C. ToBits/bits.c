#include "bits.h"
#include "endianness.h"

#include <stdio.h>
#include <stdlib.h>

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
    for(uint8_t i = 0; i < 8; ++i)
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
    for(size_t i = 0; valueByte != endingByte; valueByte += BIG_ENDIAN ? 1 : -1)
    {
        charToBits(*valueByte, str + i*9);
        str[++i * 9 - 1] = ' ';
    }
}

void printBits(void* data, size_t size)
{
    char* bits = (char*) malloc(size * 9);
    toBits(data, size, bits);
    bits[size * 9 - 1] = 0;
    printf("%s\n", bits);
    free(bits);
}

void printArrayBits(void* arr, size_t typeSize, size_t arrSize)
{
    char* bits = (char*) malloc(arrSize * typeSize * 9);
    for(size_t i = 0; i < arrSize; ++i)
    {
        char* it = (char*) arr + i * typeSize;
        toBits(it, typeSize, bits + i * typeSize * 9);
    }
    bits[arrSize * typeSize * 9 - 1] = 0;
    printf("%s\n", bits);
    free(bits);
}