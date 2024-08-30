#include <stdbool.h>

#define BIG_ENDIAN bigEndian;
#define LITTLE_ENDIAN !bigEndian;

bool bigEndian = false;

void configureEndianness();