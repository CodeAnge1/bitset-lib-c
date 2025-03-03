#include <assert.h>
#include <time.h>

#include "../src/bitset/bitset.h"

// Тестирование граничных значений
void test_boundary() {
    BitSet set = bitsetCreate(65);
    
    bitsetAdd(&set, 0);
    bitsetAdd(&set, 64);
    
    assert(bitsetContains(&set, 0) && "Ошибка: 0 не найден");
    assert(bitsetContains(&set, 64) && "Ошибка: 64 не найден");
    
    bitsetDestroy(&set);
}

// Тестирование времени выполнения
void test_performance() {
    const size_t N = 1000000;
    BitSet set = bitsetCreate(N);
    
    clock_t start = clock();

    for (size_t iter = 0; iter < N; iter++)
        bitsetAdd(&set, iter);

    clock_t end = clock();
    printf("Добавление %zu элементов заняло %.3f секунд.\n",
    N, (double)(end - start) / CLOCKS_PER_SEC);
    
    bitsetDestroy(&set);
}

// Анализ утечек памяти (запускать с valgrind)
void test_memory_leak() {
    const size_t N = 1000;
    BitSet set = bitsetCreate(N);

    for (size_t iter = 0; iter < N; iter++)
        bitsetAdd(&set, iter);

    bitsetDestroy(&set);
}

/* Тестирование различных методов множеств */

void test_remove() {
    const size_t N = 10000;
    {
        BitSet workSet = bitsetCreate(N);
        
        int valuesForAdd[] = {0, 1, 5, 15, 50, 60, 252, 22, 1555, 250, 252, 2};
        int valuesForRemove[] = {0, 5, 20};

        bitsetAddMany(&workSet, valuesForAdd, 12);
        assert(workSet.size == 11 && "Неправильный размер множества");
        
        bitsetRemove(&workSet, 15);
        assert(workSet.size == 10 && "Неправильный размер множества");
        assert(!bitsetContains(&workSet, 15) && "Элемент не был удалён");

        bitsetRemoveMany(&workSet, valuesForRemove, 3);
        assert(workSet.size == 8 && "Неправильный размер множества");
        assert(!bitsetContains(&workSet, 0) && "Элемент не был удалён");
        assert(!bitsetContains(&workSet, 5) && "Элемент не был удалён");
    }
}

void test_subset() {
    size_t smallerSize = 500;
    size_t biggerSize = 1000;

    {
        BitSet smallerSet = bitsetCreate(smallerSize);
        BitSet biggerSet = bitsetCreate(biggerSize);

        int values[] = {0, 1, 5, 15, 50, 60, 252, 22, 250, 252, 2};

        bitsetAddMany(&smallerSet, values, 12);
        bitsetAddMany(&biggerSet, values, 12);
        
        assert(setIsSubset(&smallerSet, &biggerSet) && "Ошибка, множество не является подмножеством");
    }

    {
        BitSet smallerSet = bitsetCreate(smallerSize);
        BitSet biggerSet = bitsetCreate(biggerSize);
        
        int smallerValues[] = {2, 6, 11, 100};
        int biggerValues[] = {0, 1, 2, 5, 15, 50, 60};

        bitsetAddMany(&smallerSet, smallerValues, 4);
        bitsetAddMany(&biggerSet, biggerValues, 7);
        
        assert(!setIsSubset(&smallerSet, &biggerSet) && "Ошибка, множество является подмножеством");
    }
}

void test_strict_subset() {
    size_t smallerSize = 500;
    size_t biggerSize = 1000;

    {
        BitSet smallerSet = bitsetCreate(smallerSize);
        BitSet biggerSet = bitsetCreate(biggerSize);

        int values[] = {0, 1, 5, 15, 50, 60, 252, 22, 250, 252, 2};

        bitsetAddMany(&smallerSet, values, 12);
        bitsetAddMany(&biggerSet, values, 12);
        
        assert(!setIsStrictSubset(&smallerSet, &biggerSet) && "Ошибка, множество не является подмножеством");
    }

    {
        BitSet smallerSet = bitsetCreate(smallerSize);
        BitSet biggerSet = bitsetCreate(biggerSize);

        int smallerValues[] = {2, 6, 11, 100};
        int biggerValues[] = {0, 2, 6, 11, 100, 150};

        bitsetAddMany(&smallerSet, smallerValues, 12);
        bitsetAddMany(&biggerSet, biggerValues, 12);

        assert(setIsStrictSubset(&smallerSet, &biggerSet) && "Ошибка, множество не является подмножеством");
    }
}

void test_union() {
    const size_t N = 250;
    
    {
        BitSet set1 = bitsetCreate(N);
        BitSet set2 = bitsetCreate(N);
        BitSet expectedSet = bitsetCreate(N);

        for (size_t iter = 0; iter < N; iter += 2) {
            bitsetAdd(&set1, iter);
        }
        for (size_t iter = 1; iter < N; iter += 2) {
            bitsetAdd(&set2, iter);
        }
        for (size_t iter = 0; iter < N; iter++) {
            bitsetAdd(&expectedSet, iter);
        }

        BitSet result = getSetsUnion(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && 
        "Ошибка, объединение множеств некорректно");

        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }

    {
        BitSet set1 = bitsetCreate(N);
        BitSet set2 = bitsetCreate(N);
        BitSet expectedSet = bitsetCreate(N);
        
        int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        bitsetAddMany(&set1, values, 10);
        bitsetAddMany(&set2, values, 10);
        bitsetAddMany(&expectedSet, values, 10);

        BitSet result = getSetsUnion(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && 
        "Ошибка, объединение множеств некорректно");
        
        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }

    {
        BitSet set1 = bitsetCreate(N);
        BitSet set2 = bitsetCreate(N);
        BitSet expectedSet = bitsetCreate(N);

        int values1[10] = {0, 50, 37, 117, 123, 123, 70, 124, 250, 300};
        int values2[5] = {0, 1, 58, 5, 300};
        int expectedValues[11] = {0, 1, 5, 37, 50, 58, 70, 117, 123, 124, 250};

        bitsetAddMany(&set1, values1, 10);
        bitsetAddMany(&set2, values2, 5);
        bitsetAddMany(&expectedSet, expectedValues, 11);

        BitSet result = getSetsUnion(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && 
        "Ошибка, объединение множеств некорректно");
        
        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }
}

void test_intersection() {
    const size_t N = 250;

    {
        BitSet set1 = bitsetCreate(N);
        BitSet set2 = bitsetCreate(N);
        BitSet expectedSet = bitsetCreate(N);

        for (size_t iter = 0; iter < N; iter += 2) {
            bitsetAdd(&set1, iter);
        }
        for (size_t iter = 1; iter < N; iter += 2) {
            bitsetAdd(&set2, iter);
        }

        BitSet result = getSetsIntersection(&set1, &set2);
        
        assert(setsIsEqual(&result, &expectedSet) && 
        "Ошибка, пересечение множеств некорректно");
        
        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }

    {
        BitSet set1 = bitsetCreate(N);
        BitSet set2 = bitsetCreate(N);
        BitSet expectedSet = bitsetCreate(N);
        
        int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        bitsetAddMany(&set1, values, 10);
        bitsetAddMany(&set2, values, 10);
        bitsetAddMany(&expectedSet, values, 10);

        BitSet result = getSetsIntersection(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && 
        "Ошибка, пересечение множеств некорректно");
        
        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }

    {
        BitSet set1 = bitsetCreate(N);
        BitSet set2 = bitsetCreate(N);
        BitSet expectedSet = bitsetCreate(N);

        int values1[10] = {0, 50, 37, 117, 123, 123, 70, 124, 250, 300};
        int values2[5] = {0, 1, 58, 5, 300};
        int expectedValues[1] = {0};

        bitsetAddMany(&set1, values1, 10);
        bitsetAddMany(&set2, values2, 5);
        bitsetAddMany(&expectedSet, expectedValues, 1);

        BitSet result = getSetsIntersection(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && 
        "Ошибка, пересечение множеств некорректно");
        
        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }
}

void test_difference() {
    size_t setSize = 1000;

    {
        BitSet set1 = bitsetCreate(setSize);
        BitSet set2 = bitsetCreate(setSize);
        BitSet expectedSet = bitsetCreate(setSize);

        int values1[] = {0, 1, 2, 3, 4, 5};
        int values2[] = {4, 5, 6, 7, 8, 9};
        int expectedValues[] = {0, 1, 2, 3};

        bitsetAddMany(&set1, values1, 6);
        bitsetAddMany(&set2, values2, 6);
        bitsetAddMany(&expectedSet, expectedValues, 4);

        BitSet result = getSetsDifference(&set1, &set2);

        assert(setsIsEqual(&expectedSet, &result) && "Ошибка, разность множеств некорректна");

        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }

    {
        BitSet set1 = bitsetCreate(setSize);
        BitSet set2 = bitsetCreate(setSize);
        BitSet expectedSet = bitsetCreate(setSize);

        int values1[] = {0, 1, 2, 3, 4, 5};
        int values2[] = {0, 1, 2, 3, 4, 5};
        int expectedValues[] = {};

        bitsetAddMany(&set1, values1, 6);
        bitsetAddMany(&set2, values2, 6);
        bitsetAddMany(&expectedSet, expectedValues, 0);

        BitSet result = getSetsDifference(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && "Ошибка, разность множеств некорректна");

        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }

    {
        BitSet set1 = bitsetCreate(setSize);
        BitSet set2 = bitsetCreate(setSize);
        BitSet expectedSet = bitsetCreate(setSize);

        int values1[] = {0, 1, 2, 3, 4, 5};
        int values2[] = {};
        int expectedValues[] = {0, 1, 2, 3, 4, 5};

        bitsetAddMany(&set1, values1, 6);
        bitsetAddMany(&set2, values2, 0);
        bitsetAddMany(&expectedSet, expectedValues, 6);

        BitSet result = getSetsDifference(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && "Ошибка, разность множеств некорректна");

        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }
}

void test_symmetric_difference() {
    size_t setSize = 1000;

    {
        BitSet set1 = bitsetCreate(setSize);
        BitSet set2 = bitsetCreate(setSize);
        BitSet expectedSet = bitsetCreate(setSize);

        int values1[] = {1, 6, 14, 24, 33, 75};
        int values2[] = {14, 24, 33, 42, 51, 60};
        int expectedValues[] = {1, 6, 42, 51, 60, 75};

        bitsetAddMany(&set1, values1, 6);
        bitsetAddMany(&set2, values2, 6);
        bitsetAddMany(&expectedSet, expectedValues, 6);

        BitSet result = getSetsSymmetricDifference(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && "Ошибка, симметричная разность множеств некорректна");

        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }

    {
        BitSet set1 = bitsetCreate(setSize);
        BitSet set2 = bitsetCreate(setSize);
        BitSet expectedSet = bitsetCreate(setSize);

        int values1[] = {3, 9, 15, 21, 27};
        int values2[] = {3, 9, 15, 21, 27};
        int expectedValues[] = {};

        bitsetAddMany(&set1, values1, 5);
        bitsetAddMany(&set2, values2, 5);
        bitsetAddMany(&expectedSet, expectedValues, 0);

        BitSet result = getSetsSymmetricDifference(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && "Ошибка, симметричная разность множеств некорректна");

        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }

    {
        BitSet set1 = bitsetCreate(setSize);
        BitSet set2 = bitsetCreate(setSize);
        BitSet expectedSet = bitsetCreate(setSize);

        int values1[] = {2, 5, 8, 11, 14};
        int values2[] = {4, 7, 10, 13, 16};
        int expectedValues[] = {2, 4, 5, 7, 8, 10, 11, 13, 14, 16};

        bitsetAddMany(&set1, values1, 5);
        bitsetAddMany(&set2, values2, 5);
        bitsetAddMany(&expectedSet, expectedValues, 10);

        BitSet result = getSetsSymmetricDifference(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && "Ошибка, симметричная разность множеств некорректна");

        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }

    {
        BitSet set1 = bitsetCreate(setSize);
        BitSet set2 = bitsetCreate(setSize);
        BitSet expectedSet = bitsetCreate(setSize);

        int values1[] = {10, 20, 30, 40, 50};
        int values2[] = {};
        int expectedValues[] = {10, 20, 30, 40, 50};

        bitsetAddMany(&set1, values1, 5);
        bitsetAddMany(&set2, values2, 0);
        bitsetAddMany(&expectedSet, expectedValues, 5);

        BitSet result = getSetsSymmetricDifference(&set1, &set2);

        assert(setsIsEqual(&result, &expectedSet) && "Ошибка, симметричная разность множеств некорректна");

        bitsetDestroy(&set1);
        bitsetDestroy(&set2);
        bitsetDestroy(&result);
        bitsetDestroy(&expectedSet);
    }
}

void test_complement() {
    //
}

int main() {
    test_boundary();
    test_performance();
    test_memory_leak();
    test_remove();
    test_subset();
    test_strict_subset();
    test_union();
    test_intersection();
    test_difference();
    test_symmetric_difference();
    test_complement();

    printf("Все тесты пройдены успешно!\n");

    return 0;
}