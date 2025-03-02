#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdint.h>

void printSet(const char* setName, uint64_t* bits, int capacity);
void printBitViewOfSet(const char* setName, uint64_t* bits, int blockCount);

#endif
