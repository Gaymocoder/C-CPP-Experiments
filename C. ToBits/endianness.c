#include "endianness.h"

#include <stdint.h>

bool bigEndian = false;

void configureEndianness()
{
    bigEndian = (*((uint16_t*) "\0\x1") == 0);
}