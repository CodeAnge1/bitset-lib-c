#include "bitset.h"
#include <stdbool.h>
#include <stdint.h>

BitSet bitsetCreate(size_t capacity) {
    size_t blockCount = (capacity + 63) / 64;

    BitSet set;
    set.bits = (uint64_t*)calloc(blockCount, sizeof(int64_t));

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
    if (elementCanBeCreated(element, set->capacity) == 0) {
        int arrayBlock = element / 64;
        int elementBit = element % 64;
        set->bits[arrayBlock] |= ((int64_t)1 << elementBit);
        set->size += 1;
    }
}

void bitsetRemove(BitSet* set, int element) {
    if (elementCanBeCreated(element, set->capacity) == 0) {
        int arrayBlock = element / 64;
        int elementBit = element % 64;
        set->bits[arrayBlock] &= ~((int64_t)1 << elementBit);
        set->size -= 1;
    }
}

bool bitsetContains(BitSet* set, int element) {
    bool isContains = true;
    
    if (element < 0 || set->capacity <= (size_t)element) {
        isContains = false;
    } else {
        int arrayBlock = element / 64;
        int elementBit = element % 64;
        isContains = (set->bits[arrayBlock] >> elementBit) & 1;
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

bool setsIsEqual(BitSet* setA, BitSet* setB) {
    bool isEqual = (setA->size == setB->size);

    bool setAIsSmaller = setA->blockCount < setB->blockCount;
    size_t smallerBlockCount = setAIsSmaller ? setA->blockCount : setB->blockCount;
    size_t biggerBlockCount = setAIsSmaller ? setB->blockCount : setA->blockCount;

    for (size_t block = 0; block < smallerBlockCount && isEqual; block++) {
        if (setA->bits[block] != setB->bits[block]) {
            isEqual = false;
        }
    }

    for (size_t block = smallerBlockCount; block < biggerBlockCount && isEqual; block++) {
        if (
            (setB->bits[block] != 0) && setAIsSmaller &&
            (setA->bits[block] != 0) && !setAIsSmaller
        ) {
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
    int maxSize = setB->size;
    if (setA->size > setB->size) {
        maxSize = setA->size;
    }

    BitSet setC = bitsetCreate(maxSize);
    setC.size = maxSize;

    for (size_t block = 0; block < setC.blockCount; block++) {
        setC.bits[block] = setA->bits[block] | setB->bits[block];
    }

    return setC;
}

BitSet getSetsIntersection(BitSet* setA, BitSet* setB) {
    int maxSize = setB->size;
    if (setA->size > setB->size) {
        maxSize = setA->size;
    }

    BitSet setC = bitsetCreate(maxSize);
    setC.size = maxSize;

    for (size_t block = 0; block < setC.blockCount; block++) {
        setC.bits[block] = setA->bits[block] & setB->bits[block];
    }

    return setC;
}

BitSet getSetsDifference(BitSet* setA, BitSet* setB) {
    BitSet setC = bitsetCreate(setA->size);
    setC.size = setA->size;
    for (size_t block = 0; block < setC.blockCount; block++) {
        setC.bits[block] = setA->bits[block] & (~setB->bits[block]);
    }
    return setC;
}

BitSet getSetsSymmetricDifference(BitSet* setA, BitSet* setB) {
    int maxSize = setB->size;
    if (setA->size > setB->size) {
        maxSize = setA->size;
    }

    BitSet setC = bitsetCreate(maxSize);
    setC.size = maxSize;

    for (size_t block = 0; block < setC.blockCount; block++) {
        setC.bits[block] = setA->bits[block] ^ setB->bits[block];
    }

    return setC;
}

BitSet getComplementSet(BitSet* setA) {
    BitSet set = bitsetCreate(setA->capacity);
    set.size = setA->size;

    for (size_t block = 0; block < set.blockCount; block++) {
        set.bits[block] = ~setA->bits[block];
    }

    int excessBits = set.capacity % 64;
    set.bits[set.blockCount - 1] &= (((int64_t)1 << (excessBits + 1)) - 1);

    return set;
}
