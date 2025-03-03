#include "bitset.h"

#include <stdbool.h>
#include <stdint.h>

BitSet bitsetCreate(size_t capacity) {
    size_t blockCount = (capacity + 63) / 64;

    BitSet set;
    set.bits = (uint64_t*)calloc(blockCount, sizeof(uint64_t));

    if (memoryIsAllocated(set.bits) == 0) {
        set.blockCount = blockCount;
        set.capacity = capacity;
    } else {
        set.blockCount = 0;
        set.capacity = 0;
    }
    set.size = 0;

    return set;
}

void bitsetAdd(BitSet* set, int element) {
    if (elementCanBeCreated(element, set->capacity) == 0 &&
        !bitsetContains(set, element)
        ) {
        int arrayBlock = element / 64;
        int elementBit = element % 64;
        set->bits[arrayBlock] |= ((uint64_t)1 << (63 - elementBit));
        set->size += 1;
    }
}

void bitsetAddMany(BitSet* set, int* array, int elementsCount) {
    for (int iter = 0; iter < elementsCount; iter++) {
        bitsetAdd(set, array[iter]);
    }
}

void bitsetRemove(BitSet* set, int element) {
    if (elementCanBeCreated(element, set->capacity) == 0 && bitsetContains(set, element)) {
        int arrayBlock = element / 64;
        int elementBit = element % 64;
        set->bits[arrayBlock] &= ~((uint64_t)1 << (63 - elementBit));
        set->size -= 1;
    }
}

void bitsetRemoveMany(BitSet* set, int* array, int elementsCount) {
    for (int iter = 0; iter < elementsCount; iter++) {
        bitsetRemove(set, array[iter]);
    }
}

bool bitsetContains(BitSet* set, int element) {
    bool isContains = true;

    if (element < 0 || set->capacity < (size_t)element) {
        isContains = false;
    } else {
        int arrayBlock = element / 64;
        int elementBit = element % 64;
        isContains = (set->bits[arrayBlock] >> (63 - elementBit)) & 1;
    }

    return isContains;
}

void bitsetDestroy(BitSet* set) {
    free(set->bits);
    set->bits = NULL;
    set->blockCount = 0;
    set->capacity = 0;
    set->size = 0;
}

size_t findSetSize(BitSet* set) {
    size_t counter = 0;
    for (size_t block = 0; block < set->blockCount; block++) {
        for (int8_t iter = 0; iter < 64; iter++) {
            int8_t bit = ((set->bits[block] >> (64 - iter)) & 1);
            counter += (size_t)bit;
        }
    }
    
    return counter;
}

bool setsIsEqual(BitSet* setA, BitSet* setB) {
    bool isEqual = (setA->size == setB->size);

    for (size_t block = 0; block < setA->blockCount && isEqual; block++) {
        if (setA->bits[block] != setB->bits[block]) {
            isEqual = false;
        }
    }

    return isEqual;
}

bool setIsSubset(BitSet* setA, BitSet* setB) {
    bool isSubset = true;

    for (size_t iter = 0; iter < setA->capacity && isSubset; iter++) {
        bool numberInA = setA->bits[iter / 64] >> (iter) & 1;
        bool numberInB = setB->bits[iter / 64] >> (iter) & 1;
        if ((numberInA & numberInB) != numberInA) {
            isSubset = false;
        }
    }

    return isSubset;
}

bool setIsStrictSubset(BitSet* setA, BitSet* setB) {
    bool isStrictSubset = setIsSubset(setA, setB) && (setA->size < setB->size);

    return isStrictSubset;
}

BitSet getSetsUnion(BitSet* setA, BitSet* setB) {
    int maxCapacity = setB->capacity;
    if (setA->capacity > setB->capacity) {
        maxCapacity = setA->capacity;
    }

    BitSet setC = bitsetCreate(maxCapacity);

    for (size_t block = 0; block < setC.blockCount; block++) {
        setC.bits[block] = setA->bits[block] | setB->bits[block];
    }
    setC.size = findSetSize(&setC);

    return setC;
}

BitSet getSetsIntersection(BitSet* setA, BitSet* setB) {
    int maxCapacity = setB->capacity;
    if (setA->capacity > setB->capacity) {
        maxCapacity = setA->capacity;
    }

    BitSet setC = bitsetCreate(maxCapacity);

    for (size_t block = 0; block < setC.blockCount; block++) {
        setC.bits[block] = setA->bits[block] & setB->bits[block];
    }
    setC.size = findSetSize(&setC);

    return setC;
}

BitSet getSetsDifference(BitSet* setA, BitSet* setB) {
    BitSet setC = bitsetCreate(setA->capacity);
    for (size_t block = 0; block < setC.blockCount; block++) {
        setC.bits[block] = setA->bits[block] & (~setB->bits[block]);
    }
    setC.size = findSetSize(&setC);
    return setC;
}

BitSet getSetsSymmetricDifference(BitSet* setA, BitSet* setB) {
    int maxCapacity = setB->capacity;
    if (setA->capacity > setB->capacity) {
        maxCapacity = setA->capacity;
    }

    BitSet setC = bitsetCreate(maxCapacity);

    for (size_t block = 0; block < setC.blockCount; block++) {
        setC.bits[block] = setA->bits[block] ^ setB->bits[block];
    }
    setC.size = findSetSize(&setC);

    return setC;
}

BitSet getComplementSet(BitSet* setA) {
    BitSet set = bitsetCreate(setA->capacity);
    set.size = setA->capacity - setA->size;

    for (size_t block = 0; block < set.blockCount; block++) {
        set.bits[block] = ~setA->bits[block];
    }

    int excessBits = set.capacity % 64;
    uint64_t mask = ~(((uint64_t)1 << (64 - excessBits - 1)) - 1);
    set.bits[set.blockCount - 1] &= mask;

    return set;
}
