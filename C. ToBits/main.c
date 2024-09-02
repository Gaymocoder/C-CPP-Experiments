#include "bits.h"
#include "endianness.h"

#include <stdio.h>
#include <string.h>

int main()
{
    // Configuring endianness first
    configureEndianness();
    
    // Initializing variables of different types
    uint64_t int64 = 1023;
    char* cstr = "Hello world!";
    bool boolean = true;
    float fl = 0.85;

    // Printing their bits out with help of printBits
    printf("The bits of \"1023\"-value as uint64_t var:\n");
    printBits(&int64, sizeof(uint64_t));
    printf("\n");

    // If you copy this output to binary-code-translator, you will see "!dlrow olleH".
    // The function printBits works properly only for variables of integrated data types. No arrays, no structures
    printf("The bits of \"Hello world!\"-value as char* var (by \"printBits\"-func):\n");
    printBits(cstr, strlen(cstr));
    printf("\n");

    // The function printArrayBits works properly for arrays, but not for structures
    printf("The bits of \"Hello world!\"-value as char* var (by \"printArrayBits\"-func:\n");
    printArrayBits(cstr, sizeof(char), strlen(cstr));
    printf("\n");

    printf("The bits of \"true\"-value as bool var:\n");
    printBits(&boolean, sizeof(bool));
    printf("\n");

    printf("The bits of \"0.85\"-value as float var:\n");
    printBits(&fl, sizeof(fl));
}