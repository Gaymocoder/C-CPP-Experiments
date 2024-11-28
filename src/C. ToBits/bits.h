#ifndef __BITS_H__
#define __BITS_H__

#include <stdint.h>
#include <stddef.h>

// Due to existing such thing as endianness, there are to options: either first byte of data is also the first in RAM
// or, otherwise, it is the last one in RAM. So these function are supposed to find, where are located actual first and last bytes of data
char* beginByte(void* data, size_t size);
char* endByte(void* data, size_t size);

/*
All bytes of data will be interpreted to bits one by one, so:
    charToBits — transforms single byte to bits (bits are put into "str"-variable);
    toBits — transforms all bytes of data to bits one by one with "charToBits"-function (bits are put into "str"-variable);
    printBits — prints out bits of data got with "toBits"-function;
    printArrayBits — "printBits" for arrays, not for single values*/
    
void charToBits(char value, char* str);
void toBits(void* data, size_t size, char* str);
void printBits(void* data, size_t size);
void printArrayBits(void* arr, size_t typeSize, size_t arrSize);

#endif
