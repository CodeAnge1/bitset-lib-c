#include "errors.h"

int memoryIsAllocated(uint64_t* arr) {
    int status_code = 0;
    if (arr == NULL) {
        printf("Не удалось выделить память\n");
        status_code = -1;
    }
    return status_code;
}

int elementCanBeCreated(int element, int capacity) {
    int status_code = 0;
    if (element < 0 || capacity < element) {
        printf(
            "Число %d выходит за границы допустимых значений множества (0 <= x "
            "<= %d)\n",
            element, capacity);
        status_code = -1;
    }
    return status_code;
}
