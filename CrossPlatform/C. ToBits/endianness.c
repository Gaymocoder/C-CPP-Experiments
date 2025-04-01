#include "endianness.h"

#include <stdint.h>

bool bigEndian = false;

// It's pretty easy to check if endiannes is big or small
// We create a two-byted variable (uint16_t) with help of string constant
// In the string constant there are two bytes assigned as decimal numbers: 0 and 1
// If the first byte in memory is equeal to zero (so as in data), then the endianness is big
void configureEndianness()
{
    bigEndian = (*((uint16_t*) "\0\x1") == 0);
}
