// The endianness is the bytes order of multibyte data types, how they are placed in RAM
// If first byte of data type is placed as the first one in RAM, it is called big endian
// If first byte of data type is placed as the last one in RAM, it is called little endian

#ifndef __ENDIANNESS_H__
#define __ENDIANNESS_H__

#include <stdbool.h>

// Macroses which are created to indicate if endiannes is big or small (depending on "bigEndian"-variable)
#define GCS_BIG_ENDIAN bigEndian
#define GCS_LITTLE_ENDIAN !bigEndian

// The global bool variable which is configured with start of the program
// It indicates if the endianness is big (true) or small (false)
extern bool bigEndian;

// The function which defines the "bigEndian"-variable
void configureEndianness();

#endif
