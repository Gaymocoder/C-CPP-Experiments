#include "endianness.h"

#include <stdint.h>

void configureEndianness()
{
    bigEndian = (*((uint16_t*) "\0\x1") == 0);
}