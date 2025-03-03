#ifndef BITSET_H
#define BITSET_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../handlers/errors.h"
#include "../output/output.h"

typedef struct {
    uint64_t* bits;        // Динамический блок битов
    size_t    blockCount;  // Количество элементов динамического массива bits
    size_t    size;        // Количество блоков
    size_t    capacity;    // Максимальное число элементов в множестве
} BitSet;

/* Функции работы с множеством */
BitSet bitsetCreate(size_t capacity);
void bitsetAdd(BitSet* set, int element);
void bitsetAddMany(BitSet* set, int* array, int elementsCount);
void bitsetRemove(BitSet* set, int element);
void bitsetRemoveMany(BitSet* set, int* array, int elementsCount);
bool bitsetContains(BitSet* set, int element);
void bitsetDestroy(BitSet* set);
size_t findSetSize(BitSet* set);
bool setsIsEqual(BitSet* setA, BitSet* setB);
bool setIsSubset(BitSet* setA, BitSet* setB);
bool setIsStrictSubset(BitSet* setA, BitSet* setB);
BitSet getSetsUnion(BitSet* setA, BitSet* setB);
BitSet getSetsIntersection(BitSet* setA, BitSet* setB);
BitSet getSetsDifference(BitSet* setA, BitSet* setB);
BitSet getSetsSymmetricDifference(BitSet* setA, BitSet* setB);
BitSet getComplementSet(BitSet* setA);

#endif
