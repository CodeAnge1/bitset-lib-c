# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG

SOURCES = src/main.c src/bitset/bitset.c src/handlers/errors.c src/output/output.c

# Объектные файлы
OBJ = $(SOURCES:.c=.o)

# Финальный исполняемый файл
TARGET = bitsetMain.o

# Компиляция исполняемого файла
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Компиляция каждого .c в .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка файлов
clean:
	rm -f $(OBJ) $(TARGET)

# Перекомпиляция
rebuild:
	clean $(TARGET)
