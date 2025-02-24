#include "output.h"

void printSet(const char setName, uint64_t* bits, int capacity) {
    printf("Set %c:\n", setName);

    for (int iter = 0; iter < capacity; iter++) {
        if (((bits[iter / 64]) >> iter) & 1) {
            printf("%d, ", iter);
        }
    }

    printf("\n");
}
