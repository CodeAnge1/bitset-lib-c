#include <stdio.h>

#include "bitset/bitset.h"
#include "handlers/errors.h"
#include "output/output.h"

void example_op() {
    size_t UniversumSize = 10;

    BitSet A = bitsetCreate(UniversumSize);
    int elementsA[5] = {2, 3, 4, 5, 6};
    bitsetAddMany(&A, elementsA, 5);

    BitSet B = bitsetCreate(UniversumSize);
    int elementsB[4] = {1, 2, 4, 9};
    bitsetAddMany(&B, elementsB, 4);

    BitSet C = bitsetCreate(UniversumSize);
    int elementsC[4] = {4, 5, 7, 8};
    bitsetAddMany(&C, elementsC, 4);

    BitSet D = bitsetCreate(UniversumSize);
    int elementsD[5] = {3, 4, 6, 7, 8};
    bitsetAddMany(&D, elementsD, 5);

    BitSet Answer = bitsetCreate(UniversumSize);
    int elementsRes[9] = {0, 1, 3, 4, 6, 7, 8, 9, 10};
    bitsetAddMany(&Answer, elementsRes, 9);

    BitSet _1 = getComplementSet(&A);
    BitSet _2 = getSetsIntersection(&C, &D);
    BitSet _3 = getSetsDifference(&B, &_2);
    BitSet _4 = getSetsSymmetricDifference(&_3, &C);
    BitSet _5 = getSetsUnion(&_4, &B);
    BitSet _6 = getSetsDifference(&_5, &A);
    BitSet _7 = getComplementSet(&_6);
    BitSet _8 = getSetsIntersection(&_7, &D);
    BitSet _9 = getSetsUnion(&_1, &_8);

    printSet("Result", _9.bits, _9.capacity);
    printf("Результат %sсовпадает с массивом Answer\n", setsIsEqual(&_9, &Answer) ? "" : "не ");
}

int main() {
    example_op();
    return 0;
}
