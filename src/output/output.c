#include <stdio.h>

#include "output.h"

void printSet(const char* setName, uint64_t* bits, int capacity) {
    printf("%s:\n", setName);

    for (int iter = 0; iter <= capacity; iter++) {
        if (((bits[iter / 64]) >> (63 - iter)) & 1) {
            printf("%d ", iter);
        }
    }

    printf("\n");
}

void printBitViewOfSet(const char* setName, uint64_t* bits, int blockCount) {
    printf("%s:\n", setName);

    for (int iter = 0; iter < blockCount * 64; iter++) {
        if (iter == 64) {
            printf("\n");
        }
        if (((bits[iter / 64]) >> (63 - iter)) & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }

    printf("\n");
}
