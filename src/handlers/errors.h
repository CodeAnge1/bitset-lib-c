#ifndef ERRORS_H
#define ERRORS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int memoryIsAllocated(uint64_t* arr);
int elementCanBeCreated(int element, int capacity);

#endif