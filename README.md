# Лабораторная работа №II.1. Разработка библиотеки для операций над множествами

## Оглавление

- [Вступление](#описание-проекта)
  - [Цель проекта](#цель-работы)
  - [Задачи проекта](#основные-задачи)
  - [Структура проекта](#структура-проекта)
- [Реализация](#реализация)
  - [Особенности реализации](#особенности-реализации)
  - [Список доступных функций](#функции-реализованные-в-библиотеке)
- [Сборка и запуск](#сборка-и-запуск-проекта)
- [Тестирование и анализ](#тестирование)
  - [Тестирование](#тестирование)
  - [Анализ кода](#анализ-кода)
- [Индивидуальное задание](#индивидуальное-задание)
- [Вывод](#вывод)


## Описание проекта

Данный проект представляет собой библиотеку для работы с множествами. В ней реализованы основные операции над множествами, такие как включение, строгое включение, объединение, пересечение, разность, симметрическая разность и дополнение.


### Цель работы:

Изучить методы реализации операций над множествами в языке C, используя
инструменты разработки в ОС Линукс, а также освоить практики тестирования,
автоматического анализа и форматирования кода.


### Основные задачи:
1. Ознакомление с представлением множеств в виде битовых структур и реализация базовых
операций над множествами, включая включение, объединение, пересечение, разность,
симметрическую разность и дополнение.

2. Закрепление навыков использования механизмов динамического выделения памяти и
работы с битовыми массивами в языке C.

3. Освоение инструментов автоматизированной сборки и анализа кода, включая
использование Makefile, valgrind, clang-format, AddressSanitizer, MemorySanitizer и cppcheck.

4. Выполнение индивидуального задания, связанного с вычислением теоретико-
множественного выражения, используя разработанную библиотеку.

5. Разработка алгоритма решения индивидуального задания, написание и отладка
программы, а также тестирование на различных входных данных. Программа должна
обеспечивать ввод и корректный вывод данных согласно условиям задания. При разработке
использовать указанные инструменты для анализа кода, форматирования, поиска ошибок.


### Структура проекта
```
/bitset_project
│── src/
│   │── bitset/
│   │   │── bitset.c
│   │   │── bitset.h
│   │── handlers/
│   │   │── errors.c
│   │   │── errors.h
│   │── output/
│   │   │── output.c
│   │   │── output.h
│   │── main.c
│── tests/
│   │── tests.c
│── Makefile
│── Maketest
│── README.md
```

**Описание файлов:**
- **bitset.h/bitset.c** — реализация функций работы с множествами в битовом виде.
- **errors.h/errors.c** — функции для обработки возможных ошибок. 
- **output.h/output.c** — функции вывода данных.
- **main.c** — программа, использующая библиотеку.
- **tests.c** — модуль тестирования.
- **Makefile** — автоматизированная сборка проекта.
- **Maketest** — автоматизированная сборка проекта для тестирования.
- **README.md** — описание проекта.


## Реализация

### Особенности реализации:

Множества представлены в виде массивов чисел, где каждое число является битовой маской, в которой каждый бит двоичной записи числа соответствует отдельному элементу множества. Этот представление позволяет оптимизировать использование памяти и ускорить выполнение операций над множествами.


### Функции, реализованные в библиотеке

Доступные функции для работы с множествами:

Функция | Описание
--- | ---
`bitsetCreate()` | Создание множества
`bitsetAdd()` | Добавление элемента
`bitsetAddMany()` | Добавление нескольких элементов
`bitsetRemove()` | Удаление элемента
`bitsetRemoveMany()` | Удаление нескольких элементов
`bitsetContains()` | Проверка наличия элемента
`bitsetDestroy()` | Удаление множества
`findSetSize()` | Получение размера множества
`setsIsEqual()` | Проверка равенства
`setIsSubset()` | Проверка подмножества
`setIsStrictSubset()` | Проверка строгого подмножества
`getSetsUnion()` | Объединение
`getSetsIntersection()` | Пересечение
`getSetsDifference()` | Разность
`getSetsSymmetricDifference()` | Симметричная разность
`getComplementSet()` | Дополнение


## Сборка и запуск проекта

**Для сборки используйте следующую команду:**
```sh
make
```

**Удаление ненужных скомпилированных файлов:**
```sh
make clean
```

**Удаление всех скомпилированных файлов:**
```sh
make cleanf
```

**Пересборка проекта:**
```sh
make rebuild
```

### Запуск скомпилированной программы:
```sh
./bitsetMain
```


## Тестирование

**Сборка проекта для тестирования**
```sh
make -f Maketest
```

**Удаление ненужных скомпилированных файлов:**
```sh
make clean -f Maketest
```

**Удаление всех скомпилированных файлов:**
```sh
make cleanf -f Maketest
```

**Запуск тестов**
```sh
./bitsetMain
```


## Анализ кода

**Инструменты для отладки и анализа кода:**

- **valgrind** — проверка утечек памяти.
- **clang-format** — форматирование кода.
- **AddressSanitizer и MemorySanitizer** — динамический анализ работы с памятью.
- **cppcheck** — статический анализ кода.

**Проверка утечек памяти:**
```sh
valgrind --leak-check=full --show-leak-kinds=all ./bitsetMain
```

**Синтаксический анализ:**
```sh
cppcheck --enable=all *.c
```

**Запуск автоформатирования кода:**
```sh
clang-format -style=file *.c
```

<!--
TODO: 
- **AddressSanitizer и MemorySanitizer** — динамический анализ работы с памятью.
 -->


## Индивидуальное задание

**Условие индивидуального задания:**
```math
\overset{1}{\overline{A}}
\overset{9}{\cup}
{
  \overline{
    B 
    \stackrel{3}{-}
    C
    \stackrel{2}{\cap}
    D
    \stackrel{4}{\triangle}
    C
    \stackrel{5}{\cup}
    B
    \stackrel{6}{-}
    A
  }
}
\overset{8}{\cap}
D
```

**Заданные множества:**
```math
A = \{2, 3, 4, 5, 6\};\ B = \{1, 2, 4, 9\};\ C = \{4, 5, 7, 8\};\ D = \{3, 4, 6, 7, 8\};\ U = 10
```

**Выполнение индивидуального задания:**
```math
\_1 = \overline{A} = 
      \overline{\{2, 3, 4, 5, 6\}} = 
      \{0, 1, 7, 8, 9, 10\}
```
```math
\_2 = C \cap D = 
      \{4, 5, 7, 8\} \cap \{3, 4, 6, 7, 8\} = 
      \{4, 7, 8\}
```
```math
\_3 = B - \_2 = 
      \{1, 2, 4, 9\} - \{3, 4, 5, 6, 7, 8\} = 
      \{1, 2, 9\}
```
```math
\_4 = \_3\; \triangle\; C = 
      \{1, 2, 9\}\ \triangle\ \{4, 5, 7, 8\} = 
      \{1, 2, 4, 5, 7, 8, 9\}
```
```math
\_5 = \_4 \cup B = 
      \{1, 2, 4, 5, 7, 8, 9\} \cup \{1, 2, 4, 9\} = 
      \{1, 2, 4, 5, 7, 8, 9\}
```
```math
\_6 = \_5 - A = 
      \{1, 2, 4, 5, 7, 8, 9\} - \{2, 3, 4, 5, 6\} = 
      \{1, 7, 8, 9\}
```
```math
\_7 = \overline{\_6} = 
      \overline{\{1, 7, 8, 9\}} = 
      \{0, 2, 3, 4, 5, 6, 10\}
```
```math
\_8 = \_7 \cap D = 
      \{0, 2, 3, 4, 5, 6, 10\} \cap \{3, 4, 6, 7, 8\} = 
      \{3, 4, 6\}
```
```math
\_9 = \_1 \cup \_8 = 
      \{0, 1, 7, 8, 9, 10\} \cup \{3, 4, 6\} = 
      \{0, 1, 3, 4, 6, 7, 8, 9, 10\}
```

**Программная реализация индивидуального задания представлена в файле ```main.c```**

## Вывод
В результате работы была разработана библиотека для работы с множествами. В  библиотеке предоставлены документация и примеры, что облегчает её дальнейшее использование