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

    printf("The bits of \"Hello world!\"-value as char* var:\n");
    printBits(cstr, strlen(cstr));
    printf("\n");

    printf("The bits of \"true\"-value as bool var:\n");
    printBits(&boolean, sizeof(bool));
    printf("\n");

    printf("The bits of \"0.85\"-value as float var:\n");
    printBits(&fl, sizeof(fl));
}