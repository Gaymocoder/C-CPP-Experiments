#include "endianness.h"

void configureEndianness()
{
    bigEndian = (*((short unsigned int*) "\0\x1") == 0);
}