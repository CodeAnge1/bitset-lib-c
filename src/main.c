#include <stdio.h>
#include "bitset/bitset.h"
#include "output/output.h"
#include "handlers/errors.h"

int main() {
// Создаем множество, например мощностью 520
    BitSet work_set = bitsetCreate(520);
    // Заполняем некоторые элементы
    bitsetAdd(&work_set, 10);
    bitsetAdd(&work_set, 50);
    bitsetAdd(&work_set, 100);
    printf("Вывод в стандартный поток:\n");
    printSet('A', work_set.bits, work_set.capacity);
    bitsetDestroy(&work_set);
    return 0;
}