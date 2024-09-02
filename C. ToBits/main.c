#include "bits.h"
#include "endianness.h"

#include <stdio.h>

int main()
{
    uint64_t n = 1023;
    printBits(&n, sizeof(n));
}