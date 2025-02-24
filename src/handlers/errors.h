#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int memoryIsAllocated(uint64_t* arr);
int elementCanBeCreated(int element, int capacity);
int universumIsNotLessThanSet(int setSize, int universumSize);

#endif