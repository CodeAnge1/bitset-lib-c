#ifndef BITSET_H
#define BITSET_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../output/output.h"
#include "../handlers/errors.h"

typedef struct {
    uint64_t* bits; // Динамический блок битов
    size_t blockCount; // Количество элементов динамического массива bits
    size_t size; // Количество блоков
    size_t capacity; // Максимальное число элементов в множестве
} BitSet;

/* Функции работы с множеством */
void bitsetAdd(BitSet* set, int element);
void bitsetRemove(BitSet* set, int element);
void bitsetDestroy(BitSet* set);
bool bitsetContains(BitSet* set, int element);
bool setsIsEqual(BitSet* setA, BitSet* setB);
bool setIsSubset(BitSet* setA, BitSet* setB);
bool setIsStrictSubset(BitSet* setA, BitSet* setB);
BitSet bitsetCreate(size_t univesumSize);
BitSet getSetsUnion(BitSet* setA, BitSet* setB);
BitSet getSetsIntersection(BitSet* setA, BitSet* setB);
BitSet getSetsDifference(BitSet* setA, BitSet* setB);
BitSet getSetsSymmetricDifference(BitSet* setA, BitSet* setB);
BitSet getComplementSet(BitSet* setA);

#endif
